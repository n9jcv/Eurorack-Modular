//Clock M_D module
#include <MsTimer2.h>

unsigned long ext_count = 400;//タイマーカウント用
unsigned long old_ext_pulse = 0;
unsigned long old_int_pulse = 0;
unsigned long ext_period = 0;//周期
unsigned long ext_count_result = 0;//タイマーのカウント結果
unsigned long old_ext_count_result = 0;//タイマーのカウント結果
byte ext_pulse = 0;//外部クロック　あれば1、なければ0
byte int_pulse = 0;//内部クロック
byte ext_injudge = 1;//外部入力有無判定。あれば1,なければ0。タイマーカウントが規定値超えると判定切り替え
byte old_ext_injudge = 2;

int AD_rate = 512;//rateノブの入力
int rate = 1000;//内部クロック動作時に使用

int AD_MD = 512;//MDノブの入力値
int out_width_ch1 = 10;//アウトプットのパルス幅。
int out_width_ch2 = 10;//アウトプットのパルス幅。
int old_AD_MD = 512;//SW切り替え時のRATE値誤読対策
int MD_ch1 = 5;//マルチプル、ディバイダー判定ch1
int MD_ch2 = 5;//マルチプル、ディバイダー判定ch2
int M_period_ch1 = 0;//マルチプルの時、出力クロックの周期。マルチプルでなければ0とする。
int M_period_ch2 = 0;//マルチプルの時、出力クロックの周期。マルチプルでなければ0とする。
int M_count_ch1 = 1;//マルチプルの時、パルスごとにカウントし、設定値に達すると0に戻る
int M_count_ch2 = 1;//マルチプルの時、パルスごとにカウントし、設定値に達すると0に戻る
int D_count_ch1 = 1;//外部パルスが入るとカウントを位置上げる
int D_count_ch2 = 1;//外部パルスが入るとカウントを位置上げる
int D_full_ch1 = 1;//カウントの上限値
int D_full_ch2 = 1;//カウントの上限値
byte CH1out = 0;//0でLOW出力、1でHIGH出力
byte CH2out = 0;//0でLOW出力、1でHIGH出力
byte M_done_ch1 = 0; //マルチプルの出力確認用。ないと、1クロックで複数パルスでてしまう
byte M_done_ch2 = 0; //マルチプルの出力確認用。ないと、1クロックで複数パルスでてしまう


//---mode切り替え-------------
byte mode_sw = 1;
byte mode = 1;//1=CH1,2=CH2
byte old_mode = 0;//SW切り替え時のRATE値誤読対策
int old_MD_ch1 = 0;//スイッチ切り替え時にディバイダーのクロックが狂うバグ対策
int old_MD_ch2 = 0;//スイッチ切り替え時にディバイダーのクロックが狂うバグ対策

void setup() {
 pinMode(7, OUTPUT); //CH1out
 pinMode(8, OUTPUT); //CH2out
 pinMode(13, OUTPUT); //internal_clock_out
 pinMode(11, INPUT_PULLUP); //SW
 pinMode(3, INPUT); //ext_clock_in
 //Serial.begin(9600);

 MsTimer2::set(1, timer_count); // 1ms毎にタイマーカウント
 MsTimer2::start();//外部入力Highになったら、次のHighまでカウント
}

void loop() {
 AD_MD = analogRead(3);
 AD_rate = 1023 - analogRead(4);
 rate = AD_rate * 2 + 100;

 old_ext_pulse = ext_pulse;
 old_int_pulse = int_pulse;
 ext_pulse = digitalRead(3);

 mode_sw = digitalRead(11);
 old_mode = mode;

 old_ext_injudge = ext_injudge;

 //-----------ディバイダー出力のカウントリセット------------
 if (D_count_ch1 >= D_full_ch1) {
   D_count_ch1 = 0;
 }
 if (D_count_ch2 >= D_full_ch2) {
   D_count_ch2 = 0;
 }

 //-----------SWの読み取り---------------

 old_MD_ch1 = MD_ch1;//スイッチ切り替え時にディバイダーのクロックが狂うバグ対策
 old_MD_ch2 = MD_ch2;//スイッチ切り替え時にディバイダーのクロックが狂うバグ対策

 if ( mode_sw == 1  ) {
   mode = 1;
 }
 else if (mode_sw == 0  ) {
   mode = 2;
 }

 if ( old_mode != mode ) {//スイッチ切り替え時にディバイダーのクロックが狂うバグ対策
   old_AD_MD = AD_MD;
 }

 //---------MDノブ判定-----------------------

 if ( mode == 1 && abs(old_AD_MD - AD_MD ) > 30) { //absはスイッチ切り替え時にディバイダーのクロックが狂うバグ対策
   old_AD_MD = 1200;//abs(old_AD_MD - AD_MD ) > 30が絶対に成立するため

   if ( AD_MD >= 0 && AD_MD < 20) {
     MD_ch1 = 9;//*16
   }

   else if ( AD_MD >= 20 && AD_MD < 90) {
     MD_ch1 = 8;//*8
   }

   else if ( AD_MD >= 90 && AD_MD < 240) {
     MD_ch1 = 7;//*4
   }

   else if ( AD_MD >= 240 && AD_MD < 400) {
     MD_ch1 = 6;//*2
   }

   else if ( AD_MD >= 400 && AD_MD < 550) {
     MD_ch1 = 5;//*1
   }

   else if ( AD_MD >= 550 && AD_MD < 700) {
     MD_ch1 = 4;//1/2
   }

   else if ( AD_MD >= 700 && AD_MD < 820) {
     MD_ch1 = 3;//1/3
   }

   else if ( AD_MD >= 820 && AD_MD < 960) {
     MD_ch1 = 2;//1/4
   }

   else if ( AD_MD >= 960 && AD_MD < 1024) {
     MD_ch1 = 1;//1/8
   }
 }

 else if ( mode == 2 && abs(old_AD_MD - AD_MD ) > 30) {  //absはスイッチ切り替え時にディバイダーのクロックが狂うバグ対策
   old_AD_MD = 1200;//abs(old_AD_MD - AD_MD ) > 30が絶対に成立するため

   if ( AD_MD >= 0 && AD_MD < 20) {
     MD_ch2 = 9;//*16
   }

   else if ( AD_MD >= 20 && AD_MD < 90) {
     MD_ch2 = 8;//*8
   }

   else if ( AD_MD >= 90 && AD_MD < 240) {
     MD_ch2 = 7;//*4
   }

   else if ( AD_MD >= 240 && AD_MD < 400) {
     MD_ch2 = 6;//*2
   }

   else if ( AD_MD >= 400 && AD_MD < 550) {
     MD_ch2 = 5;//*1
   }

   else if ( AD_MD >= 550 && AD_MD < 700) {
     MD_ch2 = 4;//1/2
   }

   else if ( AD_MD >= 700 && AD_MD < 820) {
     MD_ch2 = 3;//1/3
   }

   else if ( AD_MD >= 820 && AD_MD < 960) {
     MD_ch2 = 2;//1/4
   }

   else if ( AD_MD >= 960 && AD_MD < 1024) {
     MD_ch2 = 1;//1/8
   }
 }


 switch (MD_ch1) {
   case 1:
     out_width_ch1 = ext_period / 2 / 8;
     M_period_ch1 = ext_period / 8;
     break;

   case 2:
     out_width_ch1 = ext_period / 2 / 4;
     M_period_ch1 = ext_period / 4;
     break;

   case 3:
     out_width_ch1 = ext_period / 2 / 3;
     M_period_ch1 = ext_period / 3;
     break;

   case 4:
     out_width_ch1 = ext_period / 2 / 2;
     M_period_ch1 = ext_period / 2;
     break;

   case 5:
     out_width_ch1 = ext_period / 2 ;
     M_period_ch1 = 0;
     D_full_ch1 = 1;
     break;

   case 6:
     out_width_ch1 = ext_period / 2;
     M_period_ch1 = 0;
     D_full_ch1 = 2;
     break;

   case 7:
     out_width_ch1 = ext_period / 2;
     M_period_ch1 = 0;
     D_full_ch1 = 4;
     break;

   case 8:
     out_width_ch1 = ext_period / 2;
     M_period_ch1 = 0;
     D_full_ch1 = 8;
     break;

   case 9:
     out_width_ch1 = ext_period / 2;
     M_period_ch1 = 0;
     D_full_ch1 = 16;
     break;
 }


 switch (MD_ch2) {
   case 1:
     out_width_ch2 = ext_period / 2 / 8;
     M_period_ch2 = ext_period / 8;
     break;

   case 2:
     out_width_ch2 = ext_period / 2 / 4;
     M_period_ch2 = ext_period / 4;
     break;

   case 3:
     out_width_ch2 = ext_period / 2 / 3;
     M_period_ch2 = ext_period / 3;
     break;

   case 4:
     out_width_ch2 = ext_period / 2 / 2;
     M_period_ch2 = ext_period / 2;
     break;

   case 5:
     out_width_ch2 = ext_period / 2 ;
     M_period_ch2 = 0;
     D_full_ch2 = 1;
     break;

   case 6:
     out_width_ch2 = ext_period / 2 ;
     M_period_ch2 = 0;
     D_full_ch2 = 2;
     break;

   case 7:
     out_width_ch2 = ext_period / 2 ;
     M_period_ch2 = 0;
     D_full_ch2 = 4;
     break;

   case 8:
     out_width_ch2 = ext_period / 2 ;
     M_period_ch2 = 0;
     D_full_ch2 = 8;
     break;

   case 9:
     out_width_ch2 = ext_period / 2 ;
     M_period_ch2 = 0;
     D_full_ch2 = 16;
     break;
 }

 if ( MD_ch1 != old_MD_ch1 || MD_ch2 != old_MD_ch2 ) { //スイッチ切り替え時にディバイダーのクロックが狂うバグ対策
   D_count_ch1 = 0;
   D_count_ch2 = 0;
 }

 //------------外部入力有無判定-------------------------------
 if ( ext_count > 4000 ) { //4s以上カウントが無ければ、外部入力無し判定
   ext_injudge = 0;
 }
 else if ( ext_count < 4000 && ext_pulse == 1 ) {
   ext_injudge = 1;
 }

 if ( old_ext_injudge == 1 && ext_injudge == 0 ) { //外部入力が有→無のとき
   ext_count = 0;
 }


 //---------クロック設定------------------------
 if ( ext_injudge != 0 ) { //外部クロックを使用
   if (ext_pulse == 1 && old_ext_pulse == 0) {
     old_ext_count_result = ext_count_result;//2回の平均取る用
     ext_count_result = ext_count;
     //            ext_count = 0;
     ext_period = (old_ext_count_result + ext_count_result) / 2;//外部入力周期。ばらつき低減のため2回の平均値
     //      MsTimer2::start();//外部入力Highになったら、次のHighまでカウント
   }
 }
 else if ( ext_injudge == 0) { //内部クロックを使用
   ext_period = rate;
   if ( ext_count < 5 || ext_count >= ext_period) {
     int_pulse = 1;
   }
   else if (ext_count >= 5 ) {
     int_pulse = 0;
   }

 }
 //--------------INTERNAL CLOCK出力（外部入力無い場合のみ）-----------


 //Serial.print("intclock");
 //Serial.println("");
 if ( int_pulse == 1 ) {
   digitalWrite(13, HIGH);
    //Serial.print("clockhigh");
 }
 else if ( ext_count >= ext_period / 2  ) {
   digitalWrite(13, LOW);
   //Serial.print("clocklow");
 }

 //-----------------OUT1出力------------------
 if (ext_pulse == 1 && old_ext_pulse == 0) {//外部クロック用
   D_count_ch1 ++;
   ext_count = 0;
   M_count_ch1 = 0;
   M_done_ch1 = 0;
   if ( MD_ch1 <= 4 ) {
     digitalWrite(7, HIGH);
     CH1out = 1;
   }
 }

 if (int_pulse == 1 && old_int_pulse == 0) {//内部クロック用
   D_count_ch1 ++;
   ext_count = 0;
   M_count_ch1 = 0;
   M_done_ch1 = 0;
   if ( MD_ch1 <= 4 ) {
     digitalWrite(7, HIGH);
     CH1out = 1;
   }
 }

 if ( MD_ch1 < 5 ) {
   if ( ext_count  >= M_period_ch1  * M_count_ch1  && CH1out == 0) {
     CH1out = 1;
     digitalWrite(7, HIGH);
   }
   if ( ext_count >= M_period_ch1  * M_count_ch1 + out_width_ch1  && CH1out == 1 ) {
     digitalWrite(7, LOW);
     M_count_ch1 ++;
     CH1out = 0;
   }
 }

 else if ( MD_ch1 == 5 ) {
   if (D_count_ch1 == 1 && M_done_ch1 == 0) {
     CH1out = 1;
     M_done_ch1 = 1;
     digitalWrite(7, HIGH);
   }
   if ( ext_count >=  out_width_ch1   ) {
     digitalWrite(7, LOW);
     CH1out = 0;
   }
 }

 else if ( MD_ch1 > 5 ) {
   if (D_count_ch1 == 1 && M_done_ch1 == 0) {
     CH1out = 1;
     digitalWrite(7, HIGH);
     M_done_ch1 = 1;
   }
   if ( ext_count >=  out_width_ch1   ) {
     digitalWrite(7, LOW);
     CH1out = 0;
   }
 }


 //-----------------OUT2出力------------------
 if (ext_pulse == 1 && old_ext_pulse == 0) {
   D_count_ch2 ++;
   M_count_ch2 = 0;
   M_done_ch2 = 0;
   if ( MD_ch2 <= 4 ) {
     digitalWrite(8, HIGH);
     CH2out = 1;
   }
 }

 if (int_pulse == 1 && old_int_pulse == 0) {//内部クロック用
   D_count_ch2 ++;
   M_count_ch2 = 0;
   M_done_ch2 = 0;
   if ( MD_ch2 <= 4 ) {
     digitalWrite(8, HIGH);
     CH2out = 1;
   }
 }

 if ( MD_ch2 < 5 ) {
   if ( ext_count  >= M_period_ch2  * M_count_ch2  && CH2out == 0) {
     CH2out = 1;
     digitalWrite(8, HIGH);
   }
   if ( ext_count >= M_period_ch2  * M_count_ch2 + out_width_ch2  && CH2out == 1 ) {
     digitalWrite(8, LOW);
     M_count_ch2 ++;
     CH2out = 0;
   }
 }

 else if ( MD_ch2 == 5 ) {
   if (D_count_ch2 == 1 && M_done_ch2 == 0) {
     CH2out = 1;
     M_done_ch2 = 1;
     digitalWrite(8, HIGH);
   }
   if ( ext_count >=  out_width_ch2   ) {
     digitalWrite(8, LOW);
     CH2out = 0;
   }
 }

 else if ( MD_ch2 > 5 ) {
   if (D_count_ch2 == 1 && M_done_ch2 == 0) {
     CH2out = 1;
     M_done_ch2 = 1;
     digitalWrite(8, HIGH);
   }
   if ( ext_count >=  out_width_ch2   ) {
     digitalWrite(8, LOW);
     CH2out = 0;
   }
 }


 //開発用


}

//タイマーカウント。1ms毎にカウントを増やす
void timer_count() {
 ext_count ++;
}
