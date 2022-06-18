#ifndef _GPIO_REGISTER_CLASS_
#define _GPIO_REGISTER_CLASS_

  
class GPIO_MODER
{
public:
  uint32_t MODE0:2;
  uint32_t MODE1:2;
  uint32_t MODE2:2;
  uint32_t MODE3:2;
  uint32_t MODE4:2;
  uint32_t MODE5:2;
  uint32_t MODE6:2;
  uint32_t MODE7:2;
  uint32_t MODE8:2;
  uint32_t MODE9:2;
  uint32_t MODE10:2;
  uint32_t MODE11:2;
  uint32_t MODE12:2;
  uint32_t MODE13:2;
  uint32_t MODE14:2;
  uint32_t MODE15:2;
};

class GPIO
{
public:
  const uint32_t& MODE:2;
};

  
#endif /* _GPIO_REGISTER_CLASS_ */