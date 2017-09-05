#ifndef __INTERPRETER_H__
#define __INTERPRETER_H__

#include <stdint.h>

#define MAX_LAYER_DEPTH 10

class Interpreter
{
	public:
		void setup();
		void tick();
		void onKeyDown(uint8_t phyKey);
		void onKeyUp(uint8_t phyKey);
		int getCurrentLayerId();
		bool isKeyboardDirty() const {return mIsKeyboardDirty;};
		bool isMouseDirty() const {return mIsMouseDirty;};
		const uint8_t *getHidKeycodeArray();
		const uint8_t *getMouseEvent();
	private:
		bool mIsKeyboardDirty;
		bool mIsMouseDirty;
		uint8_t mActivePhyKey[60];
		uint32_t mActiveKeyFun[60];
		int mKbMapLength;
		uint8_t mLayerStackMap[MAX_LAYER_DEPTH][2];	//0 for phy, 1 for layer
		int mLayerLength;
		uint8_t mMouseEvnetMap[8][2];
		int mMouseEventLength;
		uint8_t mHidKeycodes[8];
		uint8_t mHidMouse[4];
		

		uint32_t getKeyFun(uint8_t phyKey);
		void addKeycode(uint8_t phyKey, uint32_t keyFun);
		bool removeKeycode(uint8_t phyKey);
		void addLayer(uint8_t phyKey, uint8_t layerId);
		void removeLayer(uint8_t phyKey);
		void addMouseEvent(uint8_t phyKey, uint8_t event);
		bool removeMouseEvent(uint8_t phyKey);
};


#endif


