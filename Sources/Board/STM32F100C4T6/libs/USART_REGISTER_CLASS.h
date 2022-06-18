#ifndef _USART_REGISTER_CLASS_
#define _USART_REGISTER_CLASS_

class USART_SR
{
public:
  uint32_t PE:1;
  uint32_t FE:1;
  uint32_t NF:1;
  uint32_t ORE:1;
  uint32_t IDLE:1;
  uint32_t RXNE:1;
  uint32_t TC:1;
  uint32_t TXE:1;
  uint32_t LBD:1;
  uint32_t CTS:1;
private:
  uint32_t RESERVED:22;
};

class USART_DR
{
public:
  uint32_t DR:9;
private:
  uint32_t RESERVED:23;
};

class USART_BRR
{
public:
  uint32_t DIV_Fraction:4;
  uint32_t DIV_Mantissa:12;
  
private:
  uint32_t RESERVED:16;
};

class USART_CR1
{
public:
  uint32_t SBK:1;
  uint32_t RWU:1;
  uint32_t RE:1;
  uint32_t TE:1;
  uint32_t IDLEIE:1;
  uint32_t RXNEIE:1;
  uint32_t TCIE:1;
  uint32_t TXEIE:1;
  uint32_t PEIE:1;
  uint32_t PS:1;
  uint32_t PCE:1;
  uint32_t WAKE:1;
  uint32_t M:1;
  uint32_t UE:1;
private:
  uint32_t RESERVED0:1;
public:
  uint32_t OVER8:1;
  
private:
  uint32_t RESERVED1:16;
};

class USART_CR2
{
public:
  uint32_t ADD:4;
private:
  uint32_t RESERVED0:1;
public:
  uint32_t LBDL:1;
  uint32_t LBDIE:1;
private:
  uint32_t RESERVED1:1;
public:
  uint32_t LBCL:1;
  uint32_t CPHA:1;
  uint32_t CPOL:1;
  uint32_t CLKEN:1;
  uint32_t STOP:2;
  uint32_t LINEN:1;
  
private:
  uint32_t RESERVED2:17;
};

class USART_CR3
{
public:
  uint32_t EIE:1;
  uint32_t IREN:1;
  uint32_t IRLP:1;
  uint32_t HDSEL:1;
  uint32_t NACK:1;
  uint32_t SCEN:1;
  uint32_t DMAR:1;
  uint32_t DMAT:1;
  uint32_t RTSE:1;
  uint32_t CTSE:1;
  uint32_t CTSIE:1;
  uint32_t ONEBIT:1;
  
private:
  uint32_t RESERVED:20;
};

class USART_GTPR
{
public:
  uint32_t PSC:8;
  uint32_t GT:8;
  
private:
  uint32_t RESERVED:16;
};


class USART_Register
{
public:
  USART_SR SR;
  USART_DR DR;
  USART_BRR BRR;
  USART_CR1 CR1;
  USART_CR2 CR2;
  USART_CR3 CR3;
  USART_GTPR GTPR;
};

class USART
{
public:
  USART_Register* Instance;
};

#endif /* _USART_REGISTER_CLASS_ */