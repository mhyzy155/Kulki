#ifndef KULKI_TEXTUREMAPPING_HPP
#define KULKI_TEXTUREMAPPING_HPP

//#define FROM_DISK_ONLY

#include <filesystem>
#include <string_view>
#include <utility>

#include "mapfixed.hpp"

#ifdef FROM_DISK_ONLY
#include "rawdata.hpp"

#else
#include "rawdatabackground.hpp"
#include "rawdatabackground2.hpp"
#include "rawdataballs.hpp"
#include "rawdatabtn_no.hpp"
#include "rawdatabtn_no_pressed.hpp"
#include "rawdatabtn_ok.hpp"
#include "rawdatabtn_ok_pressed.hpp"
#include "rawdatabtn_yes.hpp"
#include "rawdatabtn_yes_pressed.hpp"
#include "rawdatacell.hpp"
#include "rawdatadigits.hpp"
#include "rawdatahint_text.hpp"
#include "rawdatalogo.hpp"
#include "rawdatamark_exclamation.hpp"
#include "rawdatamark_question.hpp"
#include "rawdatascore_box.hpp"
#include "rawdatascore_text.hpp"

#endif

namespace TextureMapping {
#ifdef FROM_DISK_ONLY
static constexpr MapFixed<std::string_view, RawDataInterfaceR, 0> map{};

#else
#define RD_PAIR(path, raw_data) std::make_pair<std::string_view, RawDataInterfaceR>(path, std::cref<const RawDataInterface>(raw_data))
static constexpr MapFixed map{RD_PAIR("../media/background.png", RD::background),
                              RD_PAIR("../media/background2.png", RD::background2),
                              RD_PAIR("../media/balls.png", RD::balls),
                              RD_PAIR("../media/btn_no_pressed.png", RD::btn_no_pressed),
                              RD_PAIR("../media/btn_no.png", RD::btn_no),
                              RD_PAIR("../media/btn_ok_pressed.png", RD::btn_ok_pressed),
                              RD_PAIR("../media/btn_ok.png", RD::btn_ok),
                              RD_PAIR("../media/btn_yes_pressed.png", RD::btn_yes_pressed),
                              RD_PAIR("../media/btn_yes.png", RD::btn_yes),
                              RD_PAIR("../media/cell.png", RD::cell),
                              RD_PAIR("../media/digits.png", RD::digits),
                              RD_PAIR("../media/hint_text.png", RD::hint_text),
                              RD_PAIR("../media/logo.png", RD::logo),
                              RD_PAIR("../media/mark_exclamation.png", RD::mark_exclamation),
                              RD_PAIR("../media/mark_question.png", RD::mark_question),
                              RD_PAIR("../media/score_box.png", RD::score_box),
                              RD_PAIR("../media/score_text.png", RD::score_text)};

#endif
};  // namespace TextureMapping

#endif