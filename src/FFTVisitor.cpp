#include <iostream>
#include <cmath>

#include "FFTVisitor.hpp"
#include "TransformationComponent.hpp"
#include "MathTypes.hpp"
#include "kiss_fftr.h"


FFTVisitor::FFTVisitor(std::string musicPath)
{
    _buffer.loadFromFile(musicPath);
    _samples = _buffer.getSamples();
    _numSamples = _buffer.getSampleCount();
    _sampleRate = _buffer.getSampleRate();
    _fourierSize = _sampleRate / 60;

    if(_fourierSize % 2 == 1) _fourierSize += 1;

    _sound.setBuffer(_buffer);
    _sound.play();
}

void FFTVisitor::operator()(FFTComponent& component)
{
	if((_currentSample + _fourierSize) > _numSamples) {
		std::cout << "max " << _max << std::endl;
		return;
	}

    kiss_fft_scalar in[_fourierSize];
    kiss_fft_cpx out[_fourierSize / 2 + 1];

    // Convert to float
    for(std::size_t i = 0; i < _fourierSize; ++i) {
        in[i] = _samples[_currentSample+i];
    }
    _currentSample += _fourierSize;

    kiss_fftr_cfg cfg;
    if((cfg = kiss_fftr_alloc(_fourierSize, 0, NULL, NULL)) != NULL) {
        kiss_fftr(cfg, in, out);
        free(cfg);
        std::size_t bin = 0;
        float amplitude = sqrt(pow(out[bin].r, 2) + pow(out[bin].i, 2));
        //std::cout << out[1].r << " " << out[1].i << " " << amplitude << std::endl;
        auto& tc = component._node.ref().getComponent<TransformationComponent>();
        tc.rotateY(amplitude*PI/6292690);
        /*for(std::size_t i = 0; i < amplitude*200/6292690; ++i) {
        	std::cout << "#";
    	}*/
    	//std::cout << std::endl;
        if(amplitude > _max) _max = amplitude;

        /*
        std::size_t i;
        for (i = 0; i < 1024; i++) {
          printf(" in[%2zu] = %+f    ", i, in[i]);
          if (i < 1024 / 2 + 1) printf("out[%2zu] = %+f , %+f", i, out[i].r, out[i].i);
          printf("\n");
        }
        */
        /*
        std::size_t i;
        for (i = 0; i < 15; i++) {
          //std::cout << "out[" << i << "] = " << out[i].r << " " << out[i].i << std::endl;
        }
        */
    } else {
        printf("Kiss FFT allocation failed\n");
        exit(-1);
    }
}