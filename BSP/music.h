//
// Created by 刘嘉俊 on 24-10-10.
//

#ifndef CLION_FREERTOS_F103C8_MUSIC_H
#define CLION_FREERTOS_F103C8_MUSIC_H

/**
  * @brief  和弦音符频率生成函数，用于伴奏琶音播放，和弦类型由全局变量chordType决定
  * @param  number：和弦的第几个音，1至4为和弦的第1至第4个音，5至8算做高八度的1至4
  * @retval 和弦音符频率
  */
int chord(char number);

/**
  * @brief  前奏播放函数
  * @param  introDrums[]：前奏鼓点1轨的数组
  * @param  introCymbals[]：前奏鼓点2轨的数组
	*	@param	beat：前奏的节拍，
	*								6表示以8分音符量化的3/4拍，
	*								8表示以8分音符量化的4/4拍，
	*								16表示以16分音符量化的4/4拍，
	*								12表示以三连音音符量化的6/8拍
  * @retval 无
  */
void introPlay(char introDrums[],char introCymbals[],char beat);


/**
  * @brief  尾声播放函数
  * @param  无
  * @retval 无
  */
void endingPlay(void);

/**
  * @brief  伴奏播放函数
  * @param  arp[]：伴奏琶音轨的数组
  * @param  drums[]：伴奏鼓点1轨的数组
  * @param  cymbals[]：伴奏鼓点2轨的数组，仅在关闭琶音轨时发声
  * @param  fillDrums[]：加花鼓点1轨的数组
  * @param  fillCymbals[]：加花鼓点2轨的数组
	*	@param	number：伴奏数组大小，需为beat的整数倍
	*	@param	beat：伴奏的节拍，
	*								6表示以8分音符量化的3/4拍，
	*								8表示以8分音符量化的4/4拍，
	*								16表示以16分音符量化的4/4拍，
	*								12表示以三连音音符量化的6/8拍
  * @retval 无
  */
void acmpPlay(char arp[],char drums[],char cymbals[],char fillDrums[],char fillCymbals[],char number,char beat);


/**
  * @brief  伴奏启动函数,输入编号以启动对应风格的伴奏
  * @param  style：伴奏风格编号
  * @retval 无
  */
void acmp(char style);


#endif //CLION_FREERTOS_F103C8_MUSIC_H
