#ifndef _ALESHALIB_H

#define _ALESHALIB_H

#include <ctype.h>
#include <string.h>

#define MAGNET_PIN            12
#define Z_STEP_PIN            4
#define Z_DIRECTION_PIN       7
#define X_STEP_PIN            2
#define X_DIRECTION_PIN       5
#define MAGIC                 8

#define DELAY_PUSH_PULL       15
#define DELAY_BETWEEN_STEPS_Z 15
#define DELAY_BETWEEN_STEPS_X 15

void alesha_init  (void);
void apush_magnet (void);
void apull_magnet (void);
void amoveL       (void);
void amoveR       (void);
void astepZ       (void);
void amoveU       (void);
void amoveD       (void);
void astepX       (void);
char acnv         (char);
void aputc        (char);
void aputs        (String);

void
alesha_init (void) {
   Serial.begin (9600);
   pinMode (MAGNET_PIN,      OUTPUT);

   pinMode (Z_STEP_PIN,      OUTPUT);
   pinMode (Z_DIRECTION_PIN, OUTPUT);
   
   pinMode (X_STEP_PIN,      OUTPUT);
   pinMode (X_DIRECTION_PIN, OUTPUT);

   pinMode      (MAGIC, OUTPUT);
   digitalWrite (MAGIC, LOW);
}

void
apush_magnet (void) {
   digitalWrite (MAGNET_PIN, HIGH);
   delay (DELAY_PUSH_PULL);
}

void
apull_magnet (void) {
   digitalWrite (MAGNET_PIN, LOW);
   delay (DELAY_PUSH_PULL);
}

void
amoveL (void) {
   digitalWrite (Z_DIRECTION_PIN, LOW);
   astepZ ();
}

void
amoveR (void) {
   digitalWrite (Z_DIRECTION_PIN, HIGH);
   astepZ ();
}

void
astepZ (void) {
   digitalWrite (Z_STEP_PIN, HIGH);
   digitalWrite (Z_STEP_PIN, LOW);
   delay (DELAY_BETWEEN_STEPS_Z);
}

void
amoveD (void) {
   digitalWrite (X_DIRECTION_PIN, LOW);
   astepX ();
}

void
amoveU (void) {
   digitalWrite (X_DIRECTION_PIN, HIGH);
   astepX ();
}

void
astepX (void) {
   digitalWrite (X_STEP_PIN, HIGH);
   digitalWrite (X_STEP_PIN, LOW);
   delay (DELAY_BETWEEN_STEPS_X);
}

char
acnv (char c) {
   switch (c) {
   case 'a':
      return 0b001000;

   case 'b':
      return 0b011000;

   case 'c':
      return 0b001001;

   case 'd':
      return 0b001011;

   case 'e':
      return 0b001010;

   case 'f':
      return 0b011001;

   case 'g':
      return 0b011011;

   case 'h':
      return 0b011010;

   case 'i':
      return 0b010001;

   case 'j':
      return 0b010011;
   
   case 'k':
      return 0b101000;
   
   case 'l':
      return 0b111000;

   case 'm':
      return 0b101001;

   case 'n':
      return 0b101011;

   case 'o':
      return 0b101010;

   case 'p':
      return 0b111001;

   case 'q':
      return 0b111011;
   
   case 'r':
      return 0b111010;

   case 's':
      return 0b110001;
   
   case 't':
      return 0b110011;

   case 'u':
      return 0b101100;

   case 'v':
      return 0b111100;

   case 'w':
      return 0b010111;

   case 'x':
      return 0b101101;
   
   case 'y':
      return 0b101111;

   case 'z':
      return 0b101110;
   }
   return 0b0;
}

void
aputc (char c) {
   c = acnv (c);
   int now = 0;
   while (now < 3) {
      if (c & (1 << now)) {
         apush_magnet ();
         delay (100);
         apull_magnet ();
         delay (100);
      }
      now++;
      for (int i = 0; i < 20; ++i)
         amoveD ();
   }
   for (int i = 0; i < 60; ++i)
      amoveU ();
   for (int i = 0; i < 25; ++i)
      amoveR ();
   while (now < 6) {
      if (c & (1 << now)) {
         apush_magnet ();
         apull_magnet ();
      }
      now++;
      for (int i = 0; i < 20; ++i)
         amoveD ();
   }
   for (int i = 0; i < 60; ++i)
      amoveU ();
   for (int i = 0; i < 25; ++i)
      amoveR ();
}

void
aputs (String s) {
   char ar[3][33];
   for (int i = 0;  i < s.length(); ++i) {
      char x = acnv(s[i]);
      ar[0][i] = (x & 1)       | ((x & 8) / 4);
      ar[1][i] = ((x & 2) / 2) | ((x & 16) / 8);
      ar[2][i] = ((x & 4) / 4) | ((x & 32) / 16);
   }
   for (int line = 0; line < 3; ++line) {
      for (int i = 0; i < s.length(); ++i) {
         if (ar[line][i] & 2) {
            apush_magnet ();
            apull_magnet ();
         }
         for (int i = 0; i < 25; ++i)
            amoveL();
         if (ar[line][i] & 1) {
            apush_magnet ();
            apull_magnet ();
         }
         for (int i = 0; i < 35; ++i)
            amoveL();
      }
      for (int i = 0; i < s.length() * 60; ++i) {
         amoveR();
      }
      for (int i = 0; i < 20; ++i) {
         amoveD();
      }
   }
   for (int i = 0; i < 20; ++i) {
      amoveD();
   }
}

#endif
