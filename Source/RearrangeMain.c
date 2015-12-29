/*
RearrangeMain.c
system independant resources for the sample rearranger
Ziad Khouri (c)1998
Final Year Project
*/

#include "RearrangeMain.h"
#include <stdlib.h>
#include <memory.h>
#include <math.h>
#include <time.h>

WaveForm Wave;
unsigned int* Offset;
unsigned int CurrOffset = 0;
SequenceBuffer Sequence;

unsigned int Disarrangement;
unsigned int Irregularity;
unsigned int Density;
unsigned int NumOffsets;

void InitOffset(){
	unsigned int i;

	Offset = (unsigned int*)malloc(NUM_OFFSETS * sizeof(unsigned int));

	for( i = 0; i < NUM_OFFSETS; i++){
		Offset[i] = UIRoundD((DEF_WAV_TOTNUMSMP / NUM_OFFSETS) * i);
	}

	CurrOffset = 0;
	return;
}

void InitWavData(){
	unsigned int i;

	Wave.SamplesPerSec = DEF_WAV_SMPPERSEC;
	Wave.TotalNumSamples = DEF_WAV_TOTNUMSMP;
	Wave.WindowSize = DEF_WAV_WNDSIZE;

	Wave.PSample = (double*)malloc(DEF_WAV_TOTNUMSMP * sizeof(double));
	Wave.PEnvelop = (double*)malloc((DEF_WAV_TOTNUMSMP / DEF_WAV_WNDSIZE) * sizeof(double));

	for(i = 0; i < Wave.TotalNumSamples ; i++){
		Wave.PSample[i] = 0;
	}

	for( i = 0; i < (Wave.TotalNumSamples / Wave.WindowSize); i++){
		Wave.PEnvelop[i] = 0;
	}	
	
	return;
}

void InitSeqData(){
	unsigned int i;
	
	Sequence.SamplesPerSec = DEF_SEQ_SMPPERSEC;
	Sequence.TotalNumSamples = DEF_WAV_TOTNUMSMP * DEF_SEQ_DURATION;
	Sequence.Resolution = DEF_SEQ_RESOLUTION;
	Sequence.Duration = DEF_SEQ_DURATION;

	Sequence.PSample = (double*)malloc(Sequence.TotalNumSamples * sizeof(double));

	for(i = 0; i < Sequence.TotalNumSamples ; i++){
		Sequence.PSample[i] = 0;
	}

	Sequence.PCell = (SequenceCell*)malloc(
		(DEF_SEQ_DURATION * DEF_SEQ_RESOLUTION)
		* sizeof(SequenceCell));

	for(i = 0; i < (DEF_SEQ_DURATION * DEF_SEQ_RESOLUTION); i++){
		(Sequence.PCell + i)->OffsetIndex = EMPTY_CELL_VAL;
	}

	return;
}

void InitSeqGen(){
	Disarrangement = DEF_SEQGEN_DISARR;
	Irregularity = DEF_SEQGEN_IRREG;
	Density = DEF_SEQGEN_DENS;
	NumOffsets = DEF_SEQGEN_NUMOFFS;
	return;
}

void CleanUp(){
	free(Offset);

	free(Wave.PSample);
	free(Wave.PEnvelop);

	free(Sequence.PSample);
	free(Sequence.PCell);
	return;
}

void MakeEnvelope(){
	unsigned int i,j;
	double stride ,temp;

	stride = Wave.TotalNumSamples / Wave.WindowSize;

	free(Wave.PEnvelop);
	Wave.PEnvelop = (double*)malloc(((int)stride + 1) * sizeof(double));

	for(i = 0; i < stride; i++){
		Wave.PEnvelop[i] = 0.0;
		for(j = 0; j < Wave.WindowSize; j++){
			temp = (i * Wave.WindowSize) + j;
			if( temp < Wave.TotalNumSamples){
				temp = fabs(Wave.PSample[(int)temp]);
				if(temp > Wave.PEnvelop[i])
					Wave.PEnvelop[i] = temp;
			}
		}
	}
	return;
}

void SetupOffsets(){
	unsigned int i;

	for( i = 0; i < NUM_OFFSETS; i++){
		Offset[i] = UIRoundD((Wave.TotalNumSamples / NUM_OFFSETS) * i);
	}

	CurrOffset = 0;
	return;
}

unsigned int UIRoundD(double dblval){
	double uintval;
	if(modf(dblval,&uintval) > 0.5)
		return((unsigned int)(uintval + 1));
	return((unsigned int)uintval);
}

void FindOnset(){
	unsigned int index;

	index = UIRoundD((double)Offset[CurrOffset] /  (double)Wave.WindowSize);
	while((Wave.PEnvelop[index - 1] < Wave.PEnvelop[index]) && (((int)index - 1) > 0))
		index--;
		
	while((Wave.PEnvelop[index + 1] <= Wave.PEnvelop[index])
		&& ((index + 1) < UIRoundD((double)Wave.TotalNumSamples / (double)Wave.WindowSize)))
		index++;
	
	Offset[CurrOffset] = index * Wave.WindowSize + UIRoundD((double)Wave.WindowSize / 2.0);
	return;
}

void ResDurChange(unsigned int NewRes, unsigned int NewDur){
	double stride,stridecnt;
	unsigned int i,j,k;
	SequenceCell* OldSeq;
	OldSeq = Sequence.PCell;
	Sequence.PCell = (SequenceCell*)malloc(
		NewRes * NewDur	* sizeof(SequenceCell));

	stride = (double)NewRes / (double)Sequence.Resolution;
	
	for(i = 0; i < (NewDur * NewRes);i++)
		(Sequence.PCell + i)->OffsetIndex = EMPTY_CELL_VAL;

	for(k = 0;(k < NewDur)
		&& (k < Sequence.Duration); k++){
		j = 0;
		stridecnt = stride;
		for(i = 0;i < NewRes;i++){
			if((double)i >= stridecnt){
				while(i >= stridecnt){
					j++;
					stridecnt += stride;	
					(Sequence.PCell + i + (k * NewRes))->OffsetIndex =
						(OldSeq + j + (k * Sequence.Resolution))->OffsetIndex;
				}
			}else{
				(Sequence.PCell + i + (k * NewRes))->OffsetIndex = 
					(OldSeq + j + (k * Sequence.Resolution))->OffsetIndex;
			}
		}
	}
	Sequence.Resolution = NewRes;
	Sequence.Duration = NewDur;
	free(OldSeq);
	return;
}

void RenderSequence(){
	unsigned int i,j;
	unsigned int CurrOffsetIndex; //For SPEED!
	unsigned int index = 0;
	unsigned int lastone = EMPTY_CELL_VAL;
	double stride,stridecnt;
	char test; //For SPEED!

	Sequence.TotalNumSamples = Sequence.Duration * Wave.TotalNumSamples;

	free(Sequence.PSample);
	Sequence.PSample = (double*)malloc(Sequence.TotalNumSamples * sizeof(double));

	stride = (double)Sequence.TotalNumSamples / ((double)Sequence.Resolution * (double)Sequence.Duration);
	stridecnt = stride;
	CurrOffsetIndex = Sequence.PCell->OffsetIndex;
	i = 0;

	for( j = 0; j < Sequence.TotalNumSamples; j++){
		if ((double)j > stridecnt){
			i++;
			stridecnt += stride;
			CurrOffsetIndex = (Sequence.PCell + i)->OffsetIndex;
		}

		test = CurrOffsetIndex != EMPTY_CELL_VAL;

		if(CurrOffsetIndex != lastone){
				lastone = CurrOffsetIndex;
				if(test)
					index = Offset[CurrOffsetIndex];
		}
		if(test){
			Sequence.PSample[j] = Wave.PSample[index];
			index++;
			if(index > Wave.TotalNumSamples)
				index = 0;
		}else{
			Sequence.PSample[j] = 0;
		}
	}	
	return;
}

void SmoothSequence(){
	unsigned int i,j,interval;
	unsigned int x_offset;
	unsigned int num_cells;
	double stride;

	interval = UIRoundD(((double)Wave.TotalNumSamples / (double)Sequence.Resolution)
		* ((double)SMOOTH_VAL / 100.0));
	if(interval > MAX_SMOOTH_VAL)
		interval = MAX_SMOOTH_VAL;
	
	num_cells = Sequence.Resolution * Sequence.Duration;
	stride = (double)Sequence.TotalNumSamples / (double)num_cells;

	for(i = 1; i < num_cells; i++){
		if((Sequence.PCell + i)->OffsetIndex
			!= (Sequence.PCell + i - 1)->OffsetIndex){
			
			x_offset = UIRoundD((double)i * stride);
			
			for(j = 0; j < interval; j++){
				Sequence.PSample[(x_offset + j) % Sequence.TotalNumSamples]
					*= ((double)j * (1.0 / (double)interval));
				
				Sequence.PSample[x_offset - j]  
					*=	((double)j * (1.0 / (double)interval));
			}
		}
	}

	if((Sequence.PCell)->OffsetIndex
		!= (Sequence.PCell + num_cells - 1)->OffsetIndex){
			
		for(j = 0; j < interval; j++){
			Sequence.PSample[j]
				*= ((double)j * (1.0 / (double)interval));
				
			Sequence.PSample[Sequence.TotalNumSamples - 1 - j]  
				*=	((double)j * (1.0 / (double)interval));
		}
	}

	return;
}

void GenerateSequence(){
	unsigned int i,j;
	unsigned int *chosen_offsets;
	int interval = 0;
	unsigned int x_offset, y_offset;
	unsigned int num_cells = Sequence.Resolution * Sequence.Duration;

	srand((unsigned)time(NULL));
	
	chosen_offsets = (unsigned int*)malloc(
		(NumOffsets * Sequence.Duration) * sizeof(unsigned int));

	/*Clear Sequence*/
	for(i = 0; i < num_cells; i++)
		(Sequence.PCell + i)->OffsetIndex = EMPTY_CELL_VAL;

	/*Fill Offsetlist*/
	for(i = 0; i < NumOffsets; i++){
		for(j = 0; j < Sequence.Duration; j++){
			chosen_offsets[i + (NumOffsets * j)]
				= UIRoundD((double)i * ((double)NUM_OFFSETS / (double)NumOffsets));
		}
	}

	/*Disarrangement*/
	for(i = 0; i < (NumOffsets * Sequence.Duration); i++){
		interval = rand() % (UIRoundD(((double)NUM_OFFSETS / 2.0 )
			* ((double)Disarrangement / (double)DEF_SEQGEN_DISARR_MAX)) + 1);
				
		if((rand() % 2) == 0)
			interval = -interval;

		chosen_offsets[i] = (chosen_offsets[i] + interval) % NUM_OFFSETS;
	}

	/*Irregularity*/
	for(i = 0; i < (NumOffsets * Sequence.Duration); i++){

		if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) <= 0.25){
			interval = rand() % (UIRoundD(8.0 * 
				((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX)) + 1);
			interval *= 8;
		}

		if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) > 0.25){
			interval = rand() % (UIRoundD(16.0 * 
				(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) -  0.25)) + 1);
			interval *= 4;
		}

		if(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) > 0.50){
			interval = rand() % (UIRoundD(32.0 * 
				(((double)Irregularity / (double)DEF_SEQGEN_IRREG_MAX) - 0.50)) + 1);
			interval *= 2;
		}

		interval = (int)UIRoundD(((double)interval / 64.0) 
			* (double)Sequence.Resolution);

		if((rand() % 2) == 0)
			interval = -interval;
		
		interval = (interval + (int)UIRoundD((double)i * 
			((double)Sequence.Resolution / (double)NumOffsets))) % num_cells;

		(Sequence.PCell + interval)->OffsetIndex = chosen_offsets[i];
	}

	/*Remove Empty Sound*/
	x_offset = 0;
	y_offset = 0;

	for(i = 0; i < num_cells ; i++){
		x_offset = (Sequence.PCell + i)->OffsetIndex;
		if(x_offset != EMPTY_CELL_VAL){
			y_offset = x_offset;
		}
		(Sequence.PCell + i)->OffsetIndex = y_offset;
	}

	/*Density*/
	y_offset = UIRoundD((double)Sequence.Resolution - ((double)Sequence.Resolution
		* ((double)Density / (double)DEF_SEQGEN_DENS_MAX)));
	for(i = 0; i < y_offset;i++){
		for(j = 0;j < Sequence.Duration;j++){
			interval = 0;
			x_offset = rand() % Sequence.Resolution;
			x_offset = x_offset + (j * Sequence.Resolution);				
			while(((Sequence.PCell + x_offset)->OffsetIndex ==
				(Sequence.PCell + ((x_offset + interval) % num_cells))->OffsetIndex)
				&& (interval <= (int)num_cells)){
				interval++;
			}
			(Sequence.PCell + ((x_offset + interval - 1) % num_cells))->OffsetIndex = EMPTY_CELL_VAL;
		}
	}

	free(chosen_offsets);		
	return;
}