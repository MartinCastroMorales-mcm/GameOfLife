#include "raylib.h"
#include <string>

class mButton {
public:
  Rectangle bounds;
  std::string text;
  Color color;
  Color hoverColor;
  Color textColor;
  bool isHover;
  int fontSize;

  void DrawButton() {
    DrawRectangleRec(this->bounds, this->isHover ? hoverColor : this->color);
    DrawText(this->text.c_str(), this->bounds.x + 20, this->bounds.y + 20,
             this->fontSize, this->textColor);
  }
};