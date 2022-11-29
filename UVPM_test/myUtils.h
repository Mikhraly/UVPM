/*
 * myUtils.h
 *
 * Created: 23.11.2022 13:33:31
 *  Author: m.gasratov
 */ 


#ifndef MYUTILS_H_
#define MYUTILS_H_


#define SET_BIT(REG, BIT) (REG |= (1<<BIT))
#define RESET_BIT(REG, BIT) (REG &= ~(1<<BIT))
#define IS_BIT_SET(REG, BIT) ((REG & (1<<BIT)) != 0)
#define IS_BIT_RESET(REG, BIT) ((REG & (1<<BIT)) == 0)


#endif /* MYUTILS_H_ */