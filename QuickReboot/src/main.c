#include <psp2/kernel/clib.h>
#include <psp2/io/fcntl.h>
#include <psp2/kernel/sysmem.h>
#include <psp2/kernel/modulemgr.h>
#include <psp2/sysmodule.h>
#include <quickmenureborn/qm_reborn.h>
#include <psp2common/power.h>

#define BUTTON_ID "quick_reboot_button"
#define SEPARATOR_ID "quick_reboot_separator"

BUTTON_HANDLER(onPress) {
	scePowerRequestColdReset();
}

void _start() __attribute__((weak, alias("module_start")));
int module_start(SceSize argc, void* args) {
	QuickMenuRebornSeparator(SEPARATOR_ID, SCE_SEPARATOR_HEIGHT);

	QuickMenuRebornRegisterWidget(BUTTON_ID, NULL, button);
	QuickMenuRebornSetWidgetSize(BUTTON_ID, 200, 75, 0, 0);
	QuickMenuRebornSetWidgetColor(BUTTON_ID, 1, 1, 1, 1);
	QuickMenuRebornSetWidgetPosition(BUTTON_ID, 0, 0, 0, 0);
	QuickMenuRebornSetWidgetLabel(BUTTON_ID, "Reboot");
	QuickMenuRebornRegisterEventHanlder(BUTTON_ID, QMR_BUTTON_RELEASE_ID, onPress, NULL);

	return 0;

}

int module_stop(SceSize argc, const void* args) {
	QuickMenuRebornUnregisterWidget(BUTTON_ID);
	QuickMenuRebornRemoveSeparator(SEPARATOR_ID);

	return 0;
}
