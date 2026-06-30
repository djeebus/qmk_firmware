#ifndef KEYMAP_CONFIG_H
#define KEYMAP_CONFIG_H

#define PERMISSIVE_HOLD

// Don't force a press that quickly follows a tap of the same key into a tap
// (auto-repeat). Improves hold detection for the shift mod-taps.
#define QUICK_TAP_TERM 0

// Auto Shift is enabled (in rules.mk) ONLY to unlock Retro Shift for the
// mod-taps. Keep every normal key behaving exactly as before -- no
// hold-to-capitalize on letters, numbers, symbols, or tab.
#define NO_AUTO_SHIFT_ALPHA
#define NO_AUTO_SHIFT_NUMERIC
#define NO_AUTO_SHIFT_SPECIAL
#define NO_AUTO_SHIFT_TAB
#define AUTO_SHIFT_NO_SETUP

// Retro Shift: when a Shift mod-tap is rolled with another key and released
// quickly (within this many ms), shift that key retroactively instead of
// emitting the tap symbol (= / -). Catches fast Shift+<letter> rolls.
#define RETRO_SHIFT 300

#endif // !USERSPACE_CONFIG_H
