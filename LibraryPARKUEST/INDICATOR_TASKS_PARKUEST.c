#include <p18cxxx.h>
#include <delays.h>
#include <GenericTypeDefs.h>
#include "PROCESSOR_PARKUEST.h"
#include "COLOR_PARKUEST.h"
#include "ComINDICADOR_PARKUEST.h"
#include "INDICATOR_TASKS_PARKUEST.h"
#include "SoftwareUART_PARKUEST.h"

unsigned char DataINDICATOR[4] = {0};
///******************************************************************************/
//unsigned char i_ind = 0;
///******************************************************************************/

void INDICATOR_TASK(void) {
    ClearWDT();
    if (ReceiveCommand2_UartSOFTWARE(&DataINDICATOR[0], 4) == 1) {
        COMMUNICATION_INDICATOR(&DataINDICATOR[0]);
        DataINDICATOR[0] = 0;
    }
}
