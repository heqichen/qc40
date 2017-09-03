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
		const uint8_t *getHidKeycodeArray();
	private:
		uint8_t mActivePhyKey[60];
		uint32_t mActiveKeyFun[60];
		uint8_t mLayerStackMap[MAX_LAYER_DEPTH][2];	//0 for phy, 1 for layer
		int mLayerLength;

		uint8_t mHidKeycodes[8];
		int mKbMapLength;

		uint32_t getKeyFun(uint8_t phyKey);
		void addKeycode(uint8_t phyKey, uint32_t keyFun);
		void removeKeycode(uint8_t phyKey);
		void addLayer(uint8_t phyKey, uint8_t layerId);
		void removeLayer(uint8_t phyKey);
};


#endif


