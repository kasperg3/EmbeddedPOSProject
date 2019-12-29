//
// Created by nikolaj on 12/29/19.
//

#ifndef EMBEDDEDPROJ_STATE_MACHINE_CONSTANTS_HPP
#define EMBEDDEDPROJ_STATE_MACHINE_CONSTANTS_HPP


enum State {
    init,
    scan,
    scan_init,
    scan_keyboard_handler,
    pay,
    pay_keyboard_handler,
    validate,
    print,
    print_keyboard_handler
};


#endif //EMBEDDEDPROJ_STATE_MACHINE_CONSTANTS_HPP
