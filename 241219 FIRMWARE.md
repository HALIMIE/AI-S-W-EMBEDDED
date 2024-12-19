# 241218

생성자: 하 
생성 일시: 2024년 12월 18일 오전 9:01
태그: Firmware

23 test 

vscode를 이용할꺼고 M3미니보드를 사용중이야. C언어를 이용해서

1. 1번스위치를 누르면 led1이깜빡이고 2번 led가 깜빡이는 코드를 만들어주고
2. 시리얼스위치를 이용한 로직 코드 하나 만들어주고
3. 주파수와 duty의 상관관계를 이용한 코드를 만들어주고
4. 모터 양방향 모터 제어를 구동하기 위한 회로를 결선 하고 pa2를

## interrupt

cpu인터럽트단자하나 그래서 공유함

interrupt controller가 중개작용

pending 인터럽트 발생 요청시 기록해놓고 대기 하는애 다뤄줌
NVIC  vic벡터 인터럽트 컨트롤러

IRQ 고정주소 nonvectored

non -vic 인터럽트가 뭐가눌리는 고정주소로 가는걸 말함 nested vectored 랑 다르다

고정주소로 가서 거기서하는 일은 누가 나를 인터럽트 걸었는지 물어보고 글로감 벡터를 주지않는 방식 무조건 글로간다 

vector방식은 인터럽트마다 이미 누가 걸었는지 알수있다. 바로 그 주소로간다

내가 쓰고있는 방식은 NVIC (nested Vectoerd Controller)

PD9인터럽트를 사용할 경우 문제를 내보면
1.무슨 register을 사용하고 어느 비트에 무슨값을 넣어야하는지 퀴즈가 나오면

1번 레지스터에서는0-3,2번 레지스터에서는 4-7,3번 레지스터에서는 8-11,4번레지스터에서는 12-15 니깐 3번 레지스터에 4-7번비트를  디폴트 0011줘야함 
2.IRQ값은?

IRQ 23

### **1. 레지스터 및 비트 설정**

1. **SYSCFG_EXTICR 설정:**
    - SYSCFG의 EXTICR 레지스터는 외부 인터럽트 라인(EXTI)을 특정 GPIO 포트(PA, PB, PC, PD 등)로 매핑하는 데 사용됩니다.
    - PD9은 EXTI9 라인에 연결됩니다. EXTICR 레지스터는 각 4비트 그룹으로 나뉘며, EXTI0~EXTI15를 제어합니다.
    
    ### 매핑 규칙:
    
    - EXTICR1: EXTI0 ~ EXTI3
    - EXTICR2: EXTI4 ~ EXTI7
    - **EXTICR3: EXTI8 ~ EXTI11**
    - EXTICR4: EXTI12 ~ EXTI15
    - PD9은 EXTI9에 해당하므로, **EXTICR3**의 **4-7비트**를 설정해야 합니다.
        - PD 포트는 `0011`으로 설정됩니다 (GPIO 포트 D를 나타냄).
    
    ### 설정 코드:
    
    ```c
    c
    코드 복사
    SYSCFG->EXTICR[2] &= ~(0b1111 << 4); // EXTICR3의 4-7비트를 클리어
    SYSCFG->EXTICR[2] |= (0b0011 << 4);  // PD 포트 매핑
    
    ```
    
2. **IRQ 설정 (NVIC):**
    - EXTI9 라인은 IRQ23에 연결됩니다.
    - Cortex-M3 기반의 NVIC에서는 EXTI9_5_IRQn이 사용되며, 이는 IRQ 번호 **23**입니다.
    
    ### 설정 코드:
    
    ```c
    c
    코드 복사
    NVIC_SetPriority(EXTI9_5_IRQn, 2); // IRQ 우선순위 설정
    NVIC_EnableIRQ(EXTI9_5_IRQn);      // IRQ 활성화
    
    ```
    
3. **EXTI 설정:**
    - EXTI9에 인터럽트를 활성화하려면, IMR(Interrupt Mask Register), RTSR(Rising Trigger Selection Register), 또는 FTSR(Falling Trigger Selection Register)을 설정해야 합니다.
    
    ### 설정 코드:
    
    ```c
    c
    코드 복사
    EXTI->IMR |= (1 << 9);    // EXTI9 활성화
    EXTI->RTSR |= (1 << 9);   // 상승 에지 트리거 설정
    EXTI->FTSR &= ~(1 << 9);  // 하강 에지 트리거 비활성화
    
    ```
    

---

### **2. IRQ 값**

- IRQ 번호는 인터럽트 요청 라인을 NVIC에 매핑할 때 사용하는 고유한 번호입니다.
- EXTI9 라인은 **EXTI9_5_IRQn**에 연결되며, 이는 **IRQ23**에 해당합니다.
- NVIC는 이 IRQ 번호를 통해 인터럽트를 처리하고 적절한 핸들러를 호출합니다.

---

### **해설**

1. **레지스터 분배 논리:**
    - SYSCFG_EXTICR는 4개의 레지스터로 구성되며, 각 레지스터는 EXTI 라인의 4비트를 제어합니다:
        - EXTICR1: EXTI0 ~ EXTI3
        - EXTICR2: EXTI4 ~ EXTI7
        - EXTICR3: EXTI8 ~ EXTI11
        - EXTICR4: EXTI12 ~ EXTI15
    - EXTI9은 EXTICR3의 4-7비트를 사용합니다.
    - GPIO 포트를 PD로 매핑하려면, 해당 비트를 `0011`로 설정해야 합니다.
2. **IRQ 번호 매핑:**
    - EXTI5~EXTI9 라인은 공용 인터럽트 핸들러 EXTI9_5_IRQn으로 처리되며, 이 핸들러의 IRQ 번호는 23입니다.
    - NVIC는 이를 사용하여 인터럽트를 활성화하고 우선순위를 지정합니다.
3. **GPIO와 EXTI 연결:**
    - SYSCFG를 통해 EXTI 라인을 원하는 GPIO 포트로 매핑한 후, EXTI와 NVIC를 통해 인터럽트를 처리할 수 있습니다.

---

### **요약**

- PD9 핀을 EXTI9에 매핑하려면:
    1. **SYSCFG_EXTICR3의 4-7비트**에 `0011` 값을 설정.
    2. IRQ 번호는 **23** (EXTI9_5_IRQn).
    3. EXTI 및 NVIC 설정을 통해 인터럽트를 활성화.

## 외부인터럽트 제어기 구조

0이면 falling 엣지 

인터럽트 발생

mask

priority

pending

n번에 인터럽트걸리면 n에 저장된 주소로 가서 수행을 처리 vector

수행다하고  펜딩클리어는 소스 클리어하고 NVIC클리어해줘야한다

클리어떄 비트연산하면안된다.

key IRQ코드 

```c
void EXTI9_5_IRQHandler(void)
{
  // EXTI Pending을 확인하여 눌린키의 번호를 UART로 출력한다
  if((EXTI->PR>>6)&0b11)
  Uart1_Printf("%x\n",((EXTI->PR>>6)&0b11));

  // EXTI[7:6] pending 및 IRQ(EXTI9_5)의 pending clear
  
  EXTI->PR = (1<<6)|(1<<7);
  NVIC_ClearPendingIRQ(23);

}

```

```c
void Main(void)
{
	Sys_Init();
	Uart1_Printf("EXTI Test\n");

	// AFIO, Port-B Clock Enable

	GPIOB->CRL &= (~(0xff<<24))|(0x44<<24);
	RCC->APB2ENR |= (1<<0)|(1<<3);

	// PB[7:6]을 입력으로 선언
	AFIO->EXTICR[1] |= (0x11<<8);
	

	// PB[7:6]을 EXTI 소스로 설정하고 Falling edge 선택, EXTI[7:6] 인터럽트 허용
	EXTI->FTSR |= (1<<6)|(1<<7);
	EXTI->PR = (1<<6)|(1<<7);
	EXTI->IMR |= (1<<6)|(1<<7);

	// EXTI[7:6] Pending Clear 및 NVIC의 인터럽트 Pending clear
	NVIC_ClearPendingIRQ(23);

	// EXTI9_5 인터럽트 허용
	NVIC_EnableIRQ(23);

	for(;;)
	{
		LED_Display(1);
		TIM2_Delay(500);
		LED_Display(2);
		TIM2_Delay(500);
	}
}

```

인터럽트베이스드 , 이벤트 드리븐

1.interrupt based

고전적 , 너무 오래 잡아먹음 

2.event driven 

그냥 받아주고 나가 키가 눌렸으면 몇번이 눌렸다 , 하고 나가 

무한루프돌다가 flag가 발생되면 체크하고 그에 맞는 일을하는거

폴링이랑 뭐가 다른건지 나중에 체크

## USART(37번)interrupt

usart1 ——→NVIC(IRQ37)

유아트는 언제 인터럽트가 발생할까

 pc에서 데이터가 수신되면 RXNEIE

송신버퍼 비면 인터럽트 걸어줘 (송신가능할떄) TXEIE

통신이 에러가 났을때

event

```c
void USART1_IRQHandler(void)
{
	// Data read from USART1->DR
  Uart1_Rx_Data = USART1->DR;

	// NVIC USART1 pending clear
  NVIC_ClearPendingIRQ(37);

	Uart1_Rx_In = 1;
}
void Uart1_RX_Interrupt_Enable(int en)  //함수화 
{
	if(en)
	{
		NVIC_ClearPendingIRQ(37);

		USART1->CR1 |= (1 << 5);

		NVIC_EnableIRQ(37);
	}

	else
	{
		USART1->CR1 &= ~(1 << 5);

		NVIC_DisableIRQ(37);

	}
}
void Main(void)
{
	Sys_Init();
	Uart1_Printf("UART Interrupt Test\n");

	Key_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);

	for(;;)
	{
		if(Key_Value)
		{
			Uart1_Printf("KEY=%d\n", Key_Value);
			Key_Value = 0;
		}

	    if(Uart1_Rx_In)
	    {
			Uart1_Printf("RX Data=%c\n", Uart1_Rx_Data);
			Uart1_Rx_In = 0;
	    }

		LED_Display(1);
		TIM2_Delay(200);
		LED_Display(2);
		TIM2_Delay(200);
	}
}

```

TIMER INTERRUPT

타이머는 언제 인터럽트가 발생할까 down일떄 0일떄 

up일때는 목표치에 도달했을때

항상인터럽트는 enable 하기 전 팬딩 클리어 

딜레이 대신에 인터럽트를 사용해서 바로바로 실행되게 

```c
void TIM4_Repeat_Interrupt_Enable(int en, int time)
{
	if(en)
	{
		Macro_Set_Bit(RCC->APB1ENR, 2);

		TIM4->CR1 = (1<<4)|(0<<3);
		TIM4->PSC = (unsigned int)(TIMXCLK/(double)TIM4_FREQ + 0.5)-1;
		TIM4->ARR = TIME4_PLS_OF_1ms * time;
		Macro_Set_Bit(TIM4->EGR,0);

		
		TIM4->SR &= (~1<<0);

	
		NVIC_ClearPendingIRQ(30);
	
		TIM4->DIER |= (1<<0);
	
		NVIC_EnableIRQ(30);
		
		TIM4->CR1 |= (1<<0); 
	}

	else
	{
		NVIC_DisableIRQ(30);
		Macro_Clear_Bit(TIM4->CR1, 0);
		Macro_Clear_Bit(TIM4->DIER, 0);
	}
}
/////////////////////////////////////////////////////////
#include "device_driver.h"

static void Sys_Init(void)
{
	Clock_Init();
	LED_Init();
	Uart_Init(115200);
	Key_Poll_Init();

	SCB->VTOR = 0x08003000;
	SCB->SHCSR = 0;
}

extern volatile int Key_Value;
extern volatile int Uart1_Rx_In;
extern volatile int Uart1_Rx_Data;
extern volatile int TIM4_Expired;

void Main(void)
{
	int d = 1;

	Sys_Init();
	Uart1_Printf("Timer Interrupt Test\n");

	Key_ISR_Enable(1);
	Uart1_RX_Interrupt_Enable(1);
	TIM4_Repeat_Interrupt_Enable(1, 200);

	for(;;)
	{
		if(Key_Value)
		{
			Uart1_Printf("KEY=%d\n", Key_Value);
			Key_Value = 0;
		}

	    if(Uart1_Rx_In)
	    {
			Uart1_Printf("RX Data=%c\n", Uart1_Rx_Data);
			Uart1_Rx_In = 0;
	    }

	    if(TIM4_Expired)
	    {
			LED_Display(d^=0x3);
			TIM4_Expired = 0;
	    }
	}
}
///////////////////////////////////////////////////////////

volatile int TIM4_Expired = 0; //flag

void TIM4_IRQHandler(void)
{
	Macro_Clear_Bit(TIM4->SR, 0);
	NVIC_ClearPendingIRQ(30);
	TIM4_Expired = 1;
}
```

# 모터프로젝트

```c
#include "stm32f10x.h"
#include <stdio.h>

// PWM 관련 매크로 정의
#define PWM_FREQUENCY 1000 // PWM 주파수: 1kHz
#define TIMER_CLOCK 72000000 // 타이머 클럭: 72MHz (예시 값)
#define MAX_DUTY 1000       // 최대 Duty 값 (1kHz 기준)

// 전역 변수
volatile uint8_t motor_speed = 0; // 1~9 단계 속도
volatile char command = 'S';      // 현재 명령 상태

void UART_Init(void);
void GPIO_Init(void);
void PWM_Init(void);
void Set_Motor_Speed(uint8_t speed);
void Motor_Control(char cmd);

int main(void) {
    SystemInit();       // 시스템 초기화
    UART_Init();        // UART 초기화
    GPIO_Init();        // GPIO 초기화
    PWM_Init();         // PWM 초기화

    while (1) {
        // 현재 명령 상태에 따라 모터 제어 수행
        Motor_Control(command);
    }
}

// UART 초기화 함수
void UART_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // USART1 클럭 활성화
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;   // GPIOA 클럭 활성화

    // PA9: TX (대체 기능 출력), PA10: RX (입력)
    GPIOA->CRH &= ~((0xF << 4) | (0xF << 8));
    GPIOA->CRH |= ((0xB << 4) | (0x4 << 8));

    USART1->BRR = (TIMER_CLOCK / 9600);  // 보드레이트 9600 설정
    USART1->CR1 |= USART_CR1_RE | USART_CR1_TE; // 송수신 활성화
    USART1->CR1 |= USART_CR1_UE;               // USART 활성화

    NVIC_EnableIRQ(USART1_IRQn);              // USART1 인터럽트 활성화
    USART1->CR1 |= USART_CR1_RXNEIE;          // RXNE 인터럽트 활성화
}

// GPIO 초기화 함수
void GPIO_Init(void) {
    RCC->APB2ENR |= RCC_APB2ENR_IOPAEN; // GPIOA 클럭 활성화

    // PA2, PA3: PWM 출력 설정 (Push-Pull)
    GPIOA->CRL &= ~((0xF << 8) | (0xF << 12));
    GPIOA->CRL |= ((0xB << 8) | (0xB << 12));
}

// PWM 초기화 함수
void PWM_Init(void) {
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN; // TIM2 클럭 활성화

    TIM2->PSC = (TIMER_CLOCK / (PWM_FREQUENCY * MAX_DUTY)) - 1; // 프리스케일러 설정
    TIM2->ARR = MAX_DUTY - 1;                                 // 자동 재로드 레지스터

    // PA2 (TIM2_CH3), PA3 (TIM2_CH4)
    TIM2->CCMR2 |= (6 << TIM_CCMR2_OC3M_Pos) | TIM_CCMR2_OC3PE;
    TIM2->CCMR2 |= (6 << TIM_CCMR2_OC4M_Pos) | TIM_CCMR2_OC4PE;
    TIM2->CCER |= TIM_CCER_CC3E | TIM_CCER_CC4E; // 채널 3, 4 활성화

    TIM2->CR1 |= TIM_CR1_CEN; // 타이머 활성화

    // 기본값 설정
    Set_Motor_Speed(0);
}

// 모터 속도 설정 함수
void Set_Motor_Speed(uint8_t speed) {
    if (speed > 9) speed = 9;

    uint16_t duty_cycle = (speed * MAX_DUTY) / 9;
    TIM2->CCR3 = duty_cycle; // PA2 (1A)
    TIM2->CCR4 = duty_cycle; // PA3 (2A)
}

// 모터 제어 함수
void Motor_Control(char cmd) {
    switch (cmd) {
        case 'S': // 정지
            TIM2->CCR3 = 0;
            TIM2->CCR4 = 0;
            break;
        case 'F': // 정회전
            TIM2->CCR3 = (motor_speed * MAX_DUTY) / 9; // PA2 활성화
            TIM2->CCR4 = 0;                            // PA3 비활성화
            break;
        case 'R': // 역회전
            TIM2->CCR3 = 0;                            // PA2 비활성화
            TIM2->CCR4 = (motor_speed * MAX_DUTY) / 9; // PA3 활성화
            break;
    }
}

// USART1 인터럽트 핸들러
void USART1_IRQHandler(void) {
    if (USART1->SR & USART_SR_RXNE) {
        char received = USART1->DR; // UART에서 수신한 데이터 읽기

        if (received >= '1' && received <= '9') {
            motor_speed = received - '0'; // 속도 값 설정 (1~9)
        } else if (received == 'S' || received == 'F' || received == 'R') {
            command = received; // 명령 업데이트
        }
    }
}

```

다음은 STM32 M3 보드에서 L293 모터 드라이버를 이용해 양방향 모터 제어와 속도 제어를 구현한 코드입니다. 이 코드는 PA2와 PA3 핀을 Push-Pull 출력으로 설정하여 모터 방향 제어를 수행하며, UART를 통해 키보드 입력을 받아 정지, 정/역회전, 그리고 속도를 제어합니다.

Motor Control L293

**코드 설명**
1. **UART**:
    ◦ 키보드 입력(S, F, R, 1~9)을 통해 모터를 제어합니다.
    ◦ `S`: 정지, `F`: 정회전, `R`: 역회전.
    ◦ `1~9`: 속도를 9단계로 설정합니다.
2. **GPIO**:
    ◦ PA2와 PA3을 PWM 출력으로 설정해 L293 모터 드라이버를 제어합니다.
3. **PWM**:
    ◦ TIM2 타이머를 사용하여 PWM 신호를 생성합니다.
    ◦ PWM 주파수는 1kHz이며, `motor_speed` 값을 기준으로 Duty Cycle을 조정해 속도를 제어합니다.
4. **명령 처리**:
    ◦ 명령이 변경될 때마다 적절한 핀을 활성화하거나 비활성화해 모터 방향과 속도를 제어합니다.
    ◦ 정/역회전 전환 시 `S` 명령을 통해 탈조 방지 구간을 추가합니다.
5. **인터럽트**:
    ◦ USART1 인터럽트를 사용하여 UART 입력 데이터를 처리합니다.

1. 1.
    
    **UART**:
    
    - ◦ 키보드 입력(S, F, R, 1~9)을 통해 모터를 제어합니다.
    - ◦ `S`: 정지, `F`: 정회전, `R`: 역회전.
    - ◦ `1~9`: 속도를 9단계로 설정합니다.
- 
- 
- 
1. 2.
    
    **GPIO**:
    
    - ◦ PA2와 PA3을 PWM 출력으로 설정해 L293 모터 드라이버를 제어합니다.
- 
1. 3.
    
    **PWM**:
    
    - ◦ TIM2 타이머를 사용하여 PWM 신호를 생성합니다.
    - ◦ PWM 주파수는 1kHz이며, `motor_speed` 값을 기준으로 Duty Cycle을 조정해 속도를 제어합니다.
- 
- 
1. 4.
    
    **명령 처리**:
    
    - ◦ 명령이 변경될 때마다 적절한 핀을 활성화하거나 비활성화해 모터 방향과 속도를 제어합니다.
    - ◦ 정/역회전 전환 시 `S` 명령을 통해 탈조 방지 구간을 추가합니다.
- 
- 
1. 5.
    
    **인터럽트**:
    
    - ◦ USART1 인터럽트를 사용하여 UART 입력 데이터를 처리합니다.
-