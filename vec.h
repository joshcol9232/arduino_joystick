#pragma once

struct Vec {
  public:
    Vec() : x_(0.0), y_(0.0) {}
    Vec(const float x, const float y) : x_(x), y_(y) {}

    void print() const {
      Serial.print("{ ");
      Serial.print(x_);
      Serial.print(", ");
      Serial.print(y_);
      Serial.print("}");
    }

    float x_, y_;
};