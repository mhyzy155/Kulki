#ifndef KULKI_TEXTBOX_HPP
#define KULKI_TEXTBOX_HPP

#include <sstream>
#include <codecvt>
#include <locale>

#include "drawablerenderer.hpp"
#include "style.hpp"
#include "text.hpp"

class TextBox : public DrawableRenderer {
  using u16ostringstream = std::basic_ostringstream<char16_t>;

  struct TextInputWrapper{
    TextInputWrapper(){
      SDL_StartTextInput();
    }

    TextInputWrapper(const TextInputWrapper&) = default;
    TextInputWrapper& operator=(const TextInputWrapper&) = default;
    TextInputWrapper(TextInputWrapper&&) = default;
    TextInputWrapper& operator=(TextInputWrapper&&) = default;

    ~TextInputWrapper(){
      SDL_StopTextInput();
    }
  };

  std::wstring_convert<std::codecvt_utf8<char16_t>, char16_t> m_converter{};
  size_t m_size_max;
  std::u16string m_string;
  size_t m_cursor_pos;
  Text m_text;
  SDL_Point m_precursor_size;
  const TextInputWrapper m_text_input{};

 public:
  TextBox(SDL_Renderer* t_renderer, const std::u16string& t_text, const SDL_Point t_shift = {0, 0}, StyleText&& t_style_text = StyleText{}, Style&& t_style = Style{}, size_t t_size_max = std::u16string{}.max_size());
  void draw() const noexcept override;
  bool react(const SDL_Event& event) override;
  const std::u16string& str() const;

};

#endif