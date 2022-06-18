#ifndef _DMA_REGISTER_CLASS_
#define _DMA_REGISTER_CLASS_

  
class DMA_CCR
{
public:
  uint32_t EN:1;
  uint32_t TCIE:1;
  uint32_t HTIE:1;
  uint32_t TEIE:1;
  uint32_t DIR:1;
  uint32_t CIRC:1;
  uint32_t PINC:1;
  uint32_t MINC:1;
  uint32_t PSIZE:2;
  uint32_t MSIZE:2;
  uint32_t PL:2;
  uint32_t MEM2MEM:1;
private:
  uint32_t RESERVED:17;
};

class DMA_CNDTR
{
public:
  uint32_t NDT:16;
private:
  uint32_t RESERVED:16;
};

class DMA_CPAR
{
public:
  uint32_t PA:32;
private:        
};

class DMA_CMAR
{
public:
  uint32_t MA:32;
private:        
};
  
class DMA_Channel
{
public:
  DMA_CCR CCR;
  DMA_CNDTR CNDTR;
  DMA_CPAR CPAR;
  DMA_CMAR CMAR;
private:
  uint32_t RESERVED;
};

class DMA_ISR_Channel1
{
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED:28;
};

class DMA_ISR_Channel2
{
private:
  uint32_t RESERVED0:4;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:24;
};

class DMA_ISR_Channel3
{
private:
  uint32_t RESERVED0:8;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:20;
};

class DMA_ISR_Channel4
{
private:
  uint32_t RESERVED0:12;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:16;
};

class DMA_ISR_Channel5
{
private:
  uint32_t RESERVED0:16;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:12;
};

class DMA_ISR_Channel6
{
private:
  uint32_t RESERVED0:20;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:8;
};

class DMA_ISR_Channel7
{
private:
  uint32_t RESERVED0:24;
public:
  uint32_t GIF:1;
  uint32_t TCIF:1;
  uint32_t HTIF:1;
  uint32_t TEIF:1;
private:
  uint32_t RESERVED1:4;
};

class DMA_IFCR_Channel1
{
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED:28;
};

class DMA_IFCR_Channel2
{
private:
  uint32_t RESERVED0:4;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:24;
};

class DMA_IFCR_Channel3
{
private:
  uint32_t RESERVED0:8;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:20;
};

class DMA_IFCR_Channel4
{
private:
  uint32_t RESERVED0:12;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:16;
};

class DMA_IFCR_Channel5
{
private:
  uint32_t RESERVED0:16;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:12;
};

class DMA_IFCR_Channel6
{
private:
  uint32_t RESERVED0:20;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:8;
};

class DMA_IFCR_Channel7
{
private:
  uint32_t RESERVED0:24;
public:
  uint32_t CGIF:1;
  uint32_t CTCIF:1;
  uint32_t CHTIF:1;
  uint32_t CTEIF:1;
private:
  uint32_t RESERVED1:4;
};

template<class DMA_ISR, class DMA_IFCR>
class DMA
{
public:
  DMA_ISR* ISR;
  DMA_IFCR* IFCR;
  DMA_Channel* Channel;
};

  
#endif /* _DMA_REGISTER_CLASS_ */