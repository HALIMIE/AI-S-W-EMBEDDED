# 241217

생성자: 하 
생성 일시: 2024년 12월 17일 오전 9:10
태그: Firmware

# TIMER

주파수(f)는 신호의 주기 (T)를 알고있을떄 구할수 있다.

f=1/T

주파수는 1초동안 반복되는 신호의 횟수

신호 주기와 주파수는 역수

펄스는 단위 시간내에서 발생하는 신호의 개수를 말하고

주파수는 1초동안 몇번의 펄스가 발생하는지 나타내며 pls/시간으로 계산할수있다.

delay 100 - 100msec

delay 20 -  20msec

1msec을 만들라면 몇펄스가 필요한가 

1msec/20usec = 50 pulse

100msec 가 지나려면  5000pulse 필요

계속 쳐다보고 있지 말고 max0xffff를 넣지말고 

내가 원하는 5000pulse값을 넣고 0될때까지 기다림

polling으로 쳐다보고 있지말고 0되면 flag발생시켜줘 

delay 구현

timer를 키고

TIMER CR1 값을 설정해준다 down count, one pulse

TIM2→CR1의 4번째 비트는 DIR upcount,downcount 결정  0이면 up /  1이면 down

TIM2→CR1의 3번째 비트는 OPM one pulse mode 0:repeat 1:oneshot

TIM2→PSC는 20usec tick이 되도록 (50KHz) 분주기 

TIM2→ARR (pls) 초기값 설정 time *50 

TIM2→EGR timer의 manaul update event를 발생시키는 레지스터

TIM2→SR timer의 상태를 파악하는 레지스터 

1업데이트 발생함 0발생안함

SR의 0번 비트를 클리어  flag를 보기위해

TIM2 →DIER  interrupt enable 0비트가 0일 경우 인터럽트 불허 1일 경우 인터럽트 허용 

while (!내가기다리는조건)

sr레지스터의 0번비트가 1이되는걸 기다리는거에 대한 부정

```c
void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (1<<3)|(1<<4);

	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = 72000/50 - 1 ;

	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM2->ARR = (time *50) ;

	// UG 이벤트 발생
	TIM2->EGR |= (1<<0);

	// Update Interrupt Pending Clear
	TIM2->SR &= ~(1<<0);

	// Update Interrupt Enable
	TIM2->DIER |=(1<<0);

	// TIM2 start
	TIM2->CR1 |= (1<<0); 

	// Wait timeout
	while((TIM2->SR & (1<<0))==0);

	// Stop and Power off
	Macro_Clear_Bit(TIM2->CR1, 0);
	Macro_Clear_Bit(TIM2->DIER, 0);
}

```

65536 pulse 초과 불과 

1.3초가 최대 time * 50

65536/50

주파수를 낮은거 프리스케일러를 높이는거 

1Km는 tick이 최소 1ms

주파수를 높이면 세세함이 높아지고 시간이 짧아진다. 

주파수를 낮게하면 세세함이 줄어들지만  시간이 길어진다.

```c
void TIM2_Delay(int time)
{
	int i;
	unsigned int t = TIME2_PLS_OF_1ms * time;

	Macro_Set_Bit(RCC->APB1ENR, 0);

	TIM2->PSC = (unsigned int)(TIMXCLK/(double)TIM2_FREQ + 0.5)-1;
	TIM2->CR1 = (1<<4)|(1<<3);
	TIM2->ARR = 0xffff;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Set_Bit(TIM2->DIER, 0);

	for(i=0; i<(t/0xffffu); i++)
	{
		Macro_Set_Bit(TIM2->EGR,0);
		Macro_Clear_Bit(TIM2->SR, 0);
		Macro_Set_Bit(TIM2->CR1, 0);
		while(Macro_Check_Bit_Clear(TIM2->SR, 0));
	}

	TIM2->ARR = t % 0xffffu;
	Macro_Set_Bit(TIM2->EGR,0);
	Macro_Clear_Bit(TIM2->SR, 0);
	Macro_Set_Bit(TIM2->CR1, 0);
	while (Macro_Check_Bit_Clear(TIM2->SR, 0));

	Macro_Clear_Bit(TIM2->CR1, 0);
	Macro_Clear_Bit(TIM2->DIER, 0);
}

```

timer - stopwatch, delay, repeat 

void TIM2_Delay(int time)
{
	Macro_Set_Bit(RCC->APB1ENR, 0);

	// TIM2 CR1 설정: down count, one pulse
	TIM2->CR1 = (1<<3)|(1<<4);

	// PSC 초기값 설정 => 20usec tick이 되도록 설계 (50KHz)
	TIM2->PSC = 72000/50 - 1 ;

	// ARR 초기값 설정 => 요청한 time msec에 해당하는 초기값 설정
	TIM2->ARR = (time *50) ;

	// UG 이벤트 발생
	TIM2->EGR |= (1<<0);

	// Update Interrupt Pending Clear
	TIM2->SR &= ~(1<<0);

	// Update Interrupt Enable
	TIM2->DIER |=(1<<0);

	// TIM2 start
	TIM2->CR1 |= (1<<0); 

	// Wait timeout
	while((TIM2->SR & (1<<0))==0);

	// Stop and Power off
	Macro_Clear_Bit(TIM2->CR1, 0);
	Macro_Clear_Bit(TIM2->DIER, 0);
}

### 

주어진 `TIM2_Delay` 함수는 STM32 마이크로컨트롤러에서 TIM2 타이머를 사용하여 지연(delay)을 구현하는 코드입니다. 이 함수는 지정된 시간(밀리초 단위)에 해당하는 지연을 발생시킵니다. 코드 각 부분을 설명하여 작동 방식을 명확하게 해드리겠습니다.

### 코드 분석

1. **클록 활성화**:
    
    ```c
    c
    코드 복사
    Macro_Set_Bit(RCC->APB1ENR, 0);
    
    ```
    
    이 코드는 TIM2 타이머의 클록을 활성화하는 부분입니다. STM32에서 타이머를 사용하려면 해당 타이머의 클록을 활성화해야 하므로, `RCC->APB1ENR` 레지스터의 `TIM2` 비트를 설정하여 TIM2의 클록을 켭니다.
    
2. **타이머 제어 레지스터 설정 (CR1)**:
    
    ```c
    c
    코드 복사
    TIM2->CR1 = (1<<3)|(1<<4);
    
    ```
    
    이 코드에서 `CR1`은 타이머 제어 레지스터입니다.
    
    - `(1<<3)`은 `DIR` 비트를 설정하여 타이머를 **down count** 모드로 설정합니다. 즉, 타이머 카운터가 값을 감소시키면서 0에 도달하면 타이머가 리셋됩니다.
    - `(1<<4)`는 `OPM` 비트를 설정하여 **one pulse mode**로 설정합니다. 이 모드에서는 타이머가 한 번 카운팅 후 멈추고, 다시 시작하려면 수동으로 설정을 초기화해야 합니다.
3. **Prescaler (PSC) 설정**:
    
    ```c
    c
    코드 복사
    TIM2->PSC = 72000/50 - 1;
    
    ```
    
    `PSC`는 타이머의 프리스케일러로, 타이머의 클록 주파수를 조정합니다. STM32의 기본 타이머 클록은 72 MHz입니다. `72000 / 50 - 1`로 설정하면 타이머의 주파수는 50 kHz로 설정됩니다. 즉, 타이머의 tick 주기가 20μs가 됩니다.
    
4. **Auto-Reload Register (ARR) 설정**:
    
    ```c
    c
    코드 복사
    TIM2->ARR = (time * 50);
    
    ```
    
    `ARR`은 타이머의 자동 재로드 값입니다. 이 값은 타이머가 0에서 이 값에 도달하면 리셋되고, 이 값은 타이머의 동작 주기를 결정합니다. 여기서는 `time * 50`으로 설정되는데, `time`은 밀리초 단위로 주어집니다. `ARR` 값은 1밀리초에 50틱이므로, 요청된 밀리초에 해당하는 지연 시간만큼 타이머가 카운트하도록 설정합니다.
    
5. **Update Generation (UG) 이벤트 발생**:
    
    ```c
    c
    코드 복사
    TIM2->EGR |= (1<<0);
    
    ```
    
    `EGR` 레지스터의 `UG` (Update Generation) 비트를 설정하여 타이머 레지스터의 초기화 이벤트를 발생시킵니다. 이를 통해 설정된 `PSC` 및 `ARR` 값이 즉시 적용됩니다.
    
6. **Update Interrupt Pending Flag 초기화**:
    
    ```c
    c
    코드 복사
    TIM2->SR &= ~(1<<0);
    
    ```
    
    `SR` 레지스터는 상태 레지스터로, 타이머 상태를 나타냅니다. `SR`의 `UIF` (Update Interrupt Flag) 비트는 타이머가 업데이트 이벤트를 발생시킨 후 설정됩니다. 이 코드는 이 비트를 클리어하여, 지연 중에 타이머가 정상적으로 동작하도록 합니다.
    
7. **Update Interrupt 활성화**:
    
    ```c
    c
    코드 복사
    TIM2->DIER |= (1<<0);
    
    ```
    
    `DIER`는 인터럽트 허용 레지스터로, `UIE` (Update Interrupt Enable) 비트를 설정하여 타이머 업데이트 인터럽트를 활성화합니다. 이 비트가 설정되면, 타이머의 카운터가 지정된 값에 도달했을 때 인터럽트가 발생합니다.
    
8. **타이머 시작**:
    
    ```c
    c
    코드 복사
    TIM2->CR1 |= (1<<0);
    
    ```
    
    `CR1`의 `CEN` (Counter Enable) 비트를 설정하여 타이머 카운터를 시작합니다. 이 코드를 실행하면 타이머가 카운팅을 시작합니다.
    
9. **지연을 위한 대기**:
    
    ```c
    c
    코드 복사
    while((TIM2->SR & (1<<0)) == 0);
    
    ```
    
    이 `while` 루프는 `SR` 레지스터의 `UIF` (Update Interrupt Flag) 비트가 설정될 때까지 대기합니다. 즉, 타이머가 설정된 `ARR` 값에 도달할 때까지 대기합니다. `UIF` 비트가 설정되면 타이머가 지정된 시간을 완료했다는 의미입니다.
    
10. **타이머 정지 및 전원 끄기**:
    
    ```c
    c
    코드 복사
    Macro_Clear_Bit(TIM2->CR1, 0);
    Macro_Clear_Bit(TIM2->DIER, 0);
    
    ```
    
    - `Macro_Clear_Bit(TIM2->CR1, 0)`는 `CEN` 비트를 클리어하여 타이머를 정지합니다.
    - `Macro_Clear_Bit(TIM2->DIER, 0)`는 `UIE` 비트를 클리어하여 타이머 인터럽트를 비활성화합니다.

### 결론

이 함수는 `time` 값(밀리초 단위)에 맞는 지연을 발생시키기 위해 TIM2 타이머를 설정하고 사용합니다. 주어진 `time`에 해당하는 시간 동안 타이머를 실행하고, 타이머가 종료되면 타이머를 정지시킵니다. 이를 통해 소프트웨어에서 타이머를 이용한 지연을 효율적으로 구현할 수 있습니다.

ARR만 만지면 타이밍을 건들지않고 주기를 설정해줄수가있다.

capture / compare

외부에서 들어오는 신호를 캡쳐 

```c
void TIM3_Out_Freq_Generation(unsigned short freq)
{
	// Timer 주파수가 TIM3_FREQ가 되도록 PSC 설정
	TIM3->PSC = 8;

	// 요청한 주파수가 되도록 ARR 설정
	TIM3->ARR = 8000000/freq-1;

	// Duty Rate 50%가 되도록 CCR3 설정
	TIM3->CCR3 = (TIM3->ARR)/2;

	// Manual Update(UG 발생)
	TIM3->EGR |= (0x01);

	// Down Counter, Repeat Mode, Timer Start
	TIM3->CR1 |=(1<<4)|(1<<0);
	TIM3->CR1 &=~((1<<3));

}
```

# 12.INTERRUPT

일처리중에 내꺼먼저 ! 

exception  -돌던프로그램을 멈추고 새프로그램을 실행 

인터럽트는 갔다가 돌아옴 

key switch interrupt

cpu가 해주는 것