#pragma once

struct Vec {
  public:
    Vec() : x_(0.0), y_(0.0) {}
    Vec(const float x, const float y) : x_(x), y_(y) {}

    Vec& operator+=(const Vec& rhs) {
      x_ += rhs.x_;
      y_ += rhs.y_;
      return *this;
    }

    Vec& operator-=(const Vec& rhs) {
      x_ -= rhs.x_;
      y_ -= rhs.y_;
      return *this;
    }

    friend Vec operator-(Vec lhs, const Vec& rhs) {
      lhs -= rhs;
      return lhs;
    }

    float normSqr() const {
      return x_ * x_ + y_ * y_;
    }

    inline void print() const {
      Serial.print("{ " + String(x_) + ", " + String(y_) + " }");
    }

    float x_, y_;
};