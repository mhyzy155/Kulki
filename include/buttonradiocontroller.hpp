#ifndef KULKI_BUTTONRADIOCONTROLLER_HPP
#define KULKI_BUTTONRADIOCONTROLLER_HPP

#include "buttonswitch.hpp"
#include "macros.hpp"

class ButtonRadioController {
  ButtonSwitch* m_button_ptr = nullptr;

 public:
  void update(ButtonSwitch* t_button_ptr) {
    CHECK_THEN(m_button_ptr, uncheck());
    m_button_ptr = t_button_ptr;
  }
};

#endif