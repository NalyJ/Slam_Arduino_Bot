#include <Servo.h>
///branchements  :
/*servomoteur bleu horizontale : 2
 * servomoteur bleu verticale : 3 
 * + fils + des servomoteurs branchés à la tension des piles (4*1.5v) 
 * lidar :  fil blanc =>rx1 18 
 *          fil vert =>tx1 19
 *          fil violet et noir du => non branchés
 * capa aux bornes de lalime des piles (4*1.5 v)
 *          
*/
unsigned int distance;
int angle = 20;
boolean montee = true;

Servo servoX;
Servo servoY;


void setup(){
  
    Serial1.begin(115200);
    Serial.begin(115200);
    
    servoX.attach(12);
    servoY.attach(13);
    
    servoX.write(30);
    servoY.write(97);
    delay(1000);
}

void loop(){

  distance = mesure();
  delay(10); //  quoi sert ce delay ???
  String res = String(distance)+";"+String(angle)+";";
  Serial.println(res);

  servoX.write(angle);
  delay(40);
  if(montee){
     if(angle<=160){
      angle ++;
     }else{
        montee = false;
     }
  }else{
    if(angle>=20){
      angle --;
     }else{
        montee = true;
     }
  }
}

unsigned int mesure(){
    unsigned int t2;
    while( Serial1.available()>=9){  
      if((0x59 == Serial1.read()) && (0x59 == Serial1.read())){ //Byte1 & Byte2
          unsigned int t1 = Serial1.read(); //Byte3
          t2 = Serial1.read(); //Byte4
          
          t2 <<= 8;
          t2 += t1;
          //Serial.print(t2);
  
          Serial1.read(); //Byte5
          Serial1.read(); //Byte6
          
          for(int i=0; i<3; i++) { 
              Serial1.read(); ////Byte7,8,9
          }
      }
    }
  return t2;

}
