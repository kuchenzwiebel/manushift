# Set any rules.mk overrides for your specific keymap here.
# See rules at https://docs.qmk.fm/#/config_options?id=the-rulesmk-file


LTO_ENABLE = yes # Link Time Optimization, reduces file size
CONSOLE_ENABLE = no
COMMAND_ENABLE = no
AUTO_SHIFT_ENABLE = no
#AUTO_SHIFT_MODIFIERS = yes
DYNAMIC_MACRO_ENABLE = yes # could be deactivated for now to save on flashing size, costs around 650 bytes
SRC = matrix.c
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no     # disable underglow

UNICODE_ENABLE   = no  # deactivate default Unicode
UNICODEMAP_ENABLE = yes # activate Unicode Table with indices

NKRO_ENABLE      = no  # USB Nkey Rollover - do I need this? (saves only little on size)

TAP_DANCE_ENABLE = yes
#COMBO_ENABLE = yes

MUSIC_ENABLE = no

MOUSEKEY_ENABLE = no # costs over 1400 bytes...
EXTRAKEY_ENABLE = yes # costs ~480 bytes; for volume and multimedia control (could be done by AHK)
SPACE_CADET_ENABLE = no
GRAVE_ESC_ENABLE = no
MAGIC_ENABLE = no
