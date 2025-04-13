#pragma once

// просто прямоугольник
// нужен для создания игрового поля
class Rectangle {
public:
    Rectangle() = default;
    Rectangle(double left, double up, double right, double down){
        left_ = left;
        right_ = right;
        up_ = up;
        down_ = down;
    }
    ~Rectangle() = default;

    double GetLeft() const{
        return left_;
    }
    double GetUp() const{
        return up_;
    }
    double GetRight() const{
        return right_;
    }
    double GetDown() const{
        return down_;
    }

private:
    double left_;
    double up_;
    double right_;
    double down_;
};