key_names = [
    "None",
    #normal keys
    "Esc","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "`~","1!","2@","3#","4$","5%","6^","7&&","8*","9(","0)","-_","=+","Backspace",
    "Tab","Q","W","E","R","T","Y","U","I","O","P","[{","]}","\\|",
    "Caps","A","S","D","F","G","H","J","K","L",";:","\'\"","Enter",
    "Shift","Z","X","C","V","B","N","M","<,",">.","/?","Shift",
    "Ctrl","Win","Alt","Space","Alt","Win","Ctrl",
    #right area keys
    "PtSr","ScLk","Paus",
    "Ins","Hom","PUp",
    "Del","End","PDwn",
    "↑","←","↓","→",
    #keypad
    "NumL","/","*","-",
    "7","8","9","+",
    "4","5","6",
    "1","2","3","Enter",
    "0",".",
    #mouse keys
    "LMouse","MMouse","RMouse",
    #multi-media keys
    "VolumeDown","VolumeUp","Play/Pause","LastSong","NextSong","Mute","Calculator",
    #f13~f24
    "F13","F14","F15","F16","F17","F18",
    "F19","F20","F21","F22","F23","F24"
]
key_strings = [
    "None",
    #normal keys
    "Escape","F1","F2","F3","F4","F5","F6","F7","F8","F9","F10","F11","F12",
    "`","1","2","3","4","5","6","7","8","9","0","-","+","Backspace",
    "Tab","Q","W","E","R","T","Y","U","I","O","P","[","]","\\",
    "Caps Lock","A","S","D","F","G","H","J","K","L",";","\'","Enter",
    "LShift","Z","X","C","V","B","N","M","<",">","/","RShift",
    "LCtrl","LWin","LAlt","Space","RAlt","RWin","RCtrl",
    #right area keys
    "Print Screen","Scroll Lock","Pause",
    "Insert","Home","PageUp",
    "Delete","End","PageDown",
    "Arrow UP","Arrow Left","Arrow Down","Arrow Right",
    #keypad
    "Num Lock","/(p)","*(p)","-(p)",
    "7(p)","8(p)","9(p)","+(p)",
    "4(p)","5(p)","6(p)",
    "1(p)","2(p)","3(p)","Enter(p)",
    "0(p)",".(p)",
    #mouse keys
    "LMouse","MMouse","RMouse",
    #multi-media keys
    "VolumeDown","VolumeUp","Play/Pause","LastSong","NextSong","Mute","Calculator",
    #f13~f24
    "F13","F14","F15","F16","F17","F18",
    "F19","F20","F21","F22","F23","F24"
]
key_values = [
    0x00,
    0x29,0x3a,0x3b,0x3c,0x3d,0x3e,0x3f,0x40,0x41,0x42,0x43,0x44,0x45,
    0x35,0x1e,0x1f,0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27,0x2d,0x2e,0x2a,
    0x2b,0x14,0x1a,0x08,0x15,0x17,0x1c,0x18,0x0c,0x12,0x13,0x2f,0x30,0x31,
    0x39,0x04,0x16,0x07,0x09,0x0a,0x0b,0x0d,0x0e,0x0f,0x33,0x34,0x28,
    0x02,0x1d,0x1b,0x06,0x19,0x05,0x11,0x10,0x36,0x37,0x38,0x20,
    0x01,0x08,0x04,0x2c,0x40,0x80,0x10,
    #right area keys
    0x46,0x47,0x48,
    0x49,0x4a,0x4b,
    0x4c,0x4d,0x4e,
    0x52,0x50,0x51,0x4f,
    #keypad keys
    0x53,0x54,0x55,0x56,
    0x5f,0x60,0x61,0x57,
    0x5c,0x5d,0x5e,
    0x59,0x5a,0x5b,0x58,
    0x62,0x63,
    #mouse keys
    0x01,0x04,0x02,
    #multi-media kes
    0x01,0x02,0x04,0x08,0x10,0x20,0x40,
    #f13~f24
    0x68,0x69,0x6a,0x6b,0x6c,0x6d,
    0x6e,0x6f,0x70,0x71,0x72,0x73
]
num = 0
for num in range(len(key_strings)):
    print('_key_name['+str(num)+'] = tr("'+key_names[num]+'"); _key_string['+str(num)+'] = tr("'+key_strings[num]+'");',end = '')
    print('_key_hex['+str(num)+']='+'0x%x;'%key_values[num])
    num = num + 1