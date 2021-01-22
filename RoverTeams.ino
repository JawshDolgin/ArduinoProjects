// PROJECT  :RoverTeams
// PURPOSE  :To determine the possible Rover teams under a criteria
// DEVICE   :*
// AUTHOR   :C. D'Arcy
// DATE     :2019 01 10
// uC       :328/84/85
// COURSE   :ICS3U
// STATUS   :Working
struct ACE {
  char f;
  char l;
  uint8_t h;
  uint8_t s;
  uint8_t d;
};

ACE ACES[] = {{'D', 'B', 2, 1, 3},
  {'R', 'C', 1, 3, 2},
  {'J', 'D', 2, 3, 1},
  {'B', 'D', 3 , 2 , 1 },
  {'F', 'F', 1 , 2 , 3 },
  {'Z', 'K', 2, 3, 1},
  {'J', 'L', 1, 3, 2 },
  {'C', 'M', 1, 3, 2 },
  {'L', 'M', 1 , 2 , 3 },
  {'M', 'M', 1, 3, 2 },
  {'O', 'M', 2, 3, 1 },
  {'J', 'P', 1, 3, 2 },
  {'S', 'P', 2, 1, 3},
  {'E', 'P', 1, 3, 2 },
  {'A', 'R', 2, 1, 3 },
  {'N', 'V', 2, 3, 1 },
  {'L', 'W', 1 , 2 , 3},
  {'F', 'W', 1 , 2 , 3},
};
uint8_t numACES = sizeof(ACES) / sizeof(ACE);
uint16_t count = 0;
uint8_t hTotal;
uint8_t sTotal;
uint8_t dTotal;
uint8_t sdTotal;
#define THRESHOLD 5
#define SDTHRESHOLD 9

void setup() {
  Serial.begin(9600);
  while (!Serial);
  Serial.println("All Eligible Rover Team Compositions...");
  for (uint8_t i = 0; i < numACES; i++) {
    for (uint8_t j = 0; j < numACES; j++) {
      if (j != i) {
        for (uint8_t k = 0; k < numACES; k++) {
          if ((k != i) && (k != j)) {
            if (satisfied(i, j, k)) {
              Serial.print(ACES[i].f);
              Serial.print(ACES[i].l);
              Serial.print('\t');
              Serial.print(ACES[j].f);
              Serial.print(ACES[j].l);
              Serial.print('\t');
              Serial.print(ACES[k].f);
              Serial.print(ACES[k].l);
              Serial.print('\t');
              Serial.print(hTotal);
              Serial.print('\t');
              Serial.print(sTotal);
              Serial.print('\t');
              Serial.println(dTotal);
              count++;
            }
          }
        }
      }//k
    }//j
  }//i
  Serial.println(count);
}

boolean satisfied(uint8_t i, uint8_t j, uint8_t k) {
  hTotal = 12 - (ACES[i].h + ACES[j].h + ACES[k].h);
  sTotal = 12 - (ACES[i].s + ACES[j].s + ACES[k].s);
  dTotal = 12 - (ACES[i].d + ACES[j].d + ACES[k].d);
  return hTotal >= THRESHOLD && sTotal >= THRESHOLD && dTotal >= THRESHOLD && j>i && k>j && k>i;
  //return hTotal >= THRESHOLD && sTotal + dTotal >= SDTHRESHOLD;
  //return true;
}

void loop() {}
