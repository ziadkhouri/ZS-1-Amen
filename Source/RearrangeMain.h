/*
RearrangeMain.h
header for RearrangeMain.c
Ziad Khouri (c)1998
Final Year Project
*/

#define NUM_OFFSETS (8)

#define DEF_WAV_SMPPERSEC (44100)
#define DEF_WAV_TOTNUMSMP (16)
#define DEF_WAV_WNDSIZE (1)

#define DEF_SEQ_DURATION (1)
#define DEF_SEQ_RESOLUTION (8)
#define DEF_SEQ_SMPPERSEC (44100)

#define EMPTY_CELL_VAL (9)

#define DEF_SEQGEN_DISARR (1)
#define DEF_SEQGEN_DISARR_MIN (1)
#define DEF_SEQGEN_DISARR_MAX (100) /*Usually number of offsets*/

#define DEF_SEQGEN_IRREG (1)
#define DEF_SEQGEN_IRREG_MIN (1)
#define DEF_SEQGEN_IRREG_MAX (100)

#define DEF_SEQGEN_DENS (100)
#define DEF_SEQGEN_DENS_MIN (1)
#define DEF_SEQGEN_DENS_MAX (100)

#define DEF_SEQGEN_NUMOFFS (4)

#define SMOOTH_VAL	(10) /*Percent of cell used for fading*/
#define MAX_SMOOTH_VAL (500) 

typedef struct{
	unsigned int	SamplesPerSec;			/*Number of samples per second*/
	unsigned int	TotalNumSamples;		/*Total number of samples*/
	unsigned int	WindowSize;
	double*				PSample;						/*Pointer to sample list*/
	double*				PEnvelop;
}WaveForm;

typedef struct{
	unsigned int	OffsetIndex;				/*Offset to be played*/
/*unsigned int	Effects;	*/				/*Reserved area for effect information*/
}SequenceCell;

typedef struct{
	unsigned int	SamplesPerSec;
	unsigned int	TotalNumSamples;
	unsigned int	Resolution;
	unsigned int	Duration;
	SequenceCell*	PCell;
	double*				PSample;
}SequenceBuffer;

extern WaveForm Wave;
extern unsigned int* Offset;
extern unsigned int CurrOffset;

extern unsigned int Disarrangement;
extern unsigned int Irregularity;
extern unsigned int Density;
extern unsigned int NumOffsets;

extern SequenceBuffer Sequence;

void InitOffset();
void InitWavData();
void InitSeqData();
void InitSeqGen();
void CleanUp();

void MakeEnvelope();
void SetupOffsets();

unsigned int UIRoundD(double dblval);

void FindOnset();
void ResDurChange(unsigned int NewRes, unsigned int NewDur);
void RenderSequence();
void SmoothSequence();

void GenerateSequence();
