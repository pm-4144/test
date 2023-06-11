#pragma once

/*  Operators  */
/*  in  */
template <class T>
constexpr auto operator
  > (const std::vector<T> & _this,
     const T              & _that)
{
  return std::find(_this.begin(), _this.end(), _that);
}

template <class T>
constexpr auto operator
  < (const T              & _this,
     const std::vector<T> & _that)
{
  return _that > _this;
}

/********************************/
/*  advance  */
template <class T>
constexpr
std::vector<T> operator
  + (const std::vector<T> & _this,
     const T              & _that)
{
  auto rt = _this;
  for (const auto& i : rt) {
    if (i == _that) return rt;
  }
  rt.push_back(_that);
  rt.shrink_to_fit();
  return rt;
}

template <class T>
constexpr
std::vector<T> & operator
  += (      std::vector<T> & _this,
      const T              & _that)
{
  return (_this = _this + _that);
}

template <class T>
constexpr
std::vector<T> operator
  + (const std::vector<T> & _this,
     const std::vector<T> & _that)
{
  auto rt = _this;
  for (const auto& i : _that) {
    rt += i;
  }
  return rt;
}

template <class T>
constexpr
std::vector<T> & operator
  += (      std::vector<T> & _this,
      const std::vector<T> & _that)
{
  return (_this = _this + _that);
}


/********************************/
/*  sub  */
template <class T>
constexpr
std::vector<T> operator
  - (const std::vector<T> & _this,
     const T              & _that)
{
  if (!_this.size()) return _this;
  auto rt = _this;
#if 0
  for (auto i = rt.begin(); i < rt.end(); ++i)
    if (*i == _that) {
      rt.erase(i); break;
    }
#else
  if (auto i = rt > _that; i != rt.end())
    rt.erase(i);
#endif
  rt.shrink_to_fit();
  return rt;
}

template <class T>
constexpr
std::vector<T> & operator
  -= (      std::vector<T> & _this,
      const T              & _that)
{
  return (_this = _this - _that);
}

template <class T>
constexpr
std::vector<T> operator
  - (const std::vector<T> & _this,
     const std::vector<T> & _that)
{
  auto rt = _this;
  for (const auto& i : _that)
    rt -= i;
  return rt;
}

template <class T>
constexpr
std::vector<T> & operator
  -= (      std::vector<T> & _this,
      const std::vector<T> & _that)
{
  return (_this = _this - _that);
}


/********************************/
/*  multiply  */
template <class T>
constexpr
std::vector<T> operator
  * (const std::vector<T> & _this,
     const std::vector<T> & _that)
{
  return _this - (_this - _that);
//return _that - (_that - _this);
}

template <class T>
constexpr
std::vector<T> & operator
  *= (      std::vector<T> & _this,
      const std::vector<T> & _that)
{
  return (_this = _this * _that);
}


/********************************/
/*  divide  */
template <class T>
std::vector<T> operator
  / (const std::vector<T> & _this,
     const std::vector<T> & _that)
{
//return _this + _that - (_this * _that);
  return (_this - _that) + (_that - _this);
}

template <class T>
constexpr
std::vector<T> & operator
  /= (      std::vector<T> & _this,
      const std::vector<T> & _that)
{
  return (_this = _this / _that);
}






