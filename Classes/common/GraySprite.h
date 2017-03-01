#ifndef __GRAY_SPRITE_H__
#define __GRAY_SPRITE_H__

#include "cocos2d.h"
USING_NS_CC;
class GraySprite : public cocos2d::Sprite
{
public:

	/** 
	 * @brief 构造函数
	 */
	GraySprite();


	/** 
	 * @brief 析构函数
	 */
	virtual ~GraySprite();


	/**
	 * @brief 生成一个灰度精灵 
	 * @param [in] pszFileName 图片文件名
	 * @retval 生成成功，返回一个灰度精灵对象指针
	 * @retval 生成失败，返回 0
	 */
	static GraySprite* create(const char* pszFileName);
	static GraySprite* create(std::string spriteName,int png);
	static GraySprite* create( cocos2d::Texture2D* pTexture, const cocos2d::Rect& tRect );

	/** 
	 * @brief 初始化灰度精灵
	 * @param [in] pTexture 纹理对象
	 * @param [in] tRect 纹理裁剪区域
	 * @retval 初始化成功，返回true
	 * @retval 初始化失败，返回false
	 */
	bool initWithTexture(cocos2d::Texture2D* pTexture, const cocos2d::Rect&  tRect);


	/** 
	 * @brief 绘图事件
	 */
	 //virtual void draw(Renderer *renderer, const kmMat4 &transform, bool transformUpdated) override;

};

#endif // __MM_GRAY_SCALE_SPRITE_H__