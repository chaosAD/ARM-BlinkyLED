#include "StateDiagramLED3.h"

int main() {
  State state = {INITIAL};
  while(1)
    state = blinkLED3(state);
}
