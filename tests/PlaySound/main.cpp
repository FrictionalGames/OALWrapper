#include "OALWrapper/OAL_Funcs.h"
#include "OALWrapper/OAL_Sample.h"
#include <stdio.h>
#include <string>

void playSample(cOAL_Sample* pSample)
{
	if (pSample) {
        printf("Success\n");

        printf("Playing Sample...\n");
        printf("\tChannels : %d\n\tFrequency : %d\n", pSample->GetChannels(), pSample->GetFrequency() );

		OAL_Source_Stop ( OAL_ALL );

        int s1 = OAL_Sample_Play ( OAL_FREE, pSample, 1.0f, true, 10 );
		OAL_Source_SetPaused(s1, false);
        while (OAL_Source_IsPlaying(s1)) {
        }
		pSample = NULL;
    } else {
        printf("Failed\n");
    }
}

int main (int argc, char *argv[])
{
    string strFilename;

	if ( argc <= 1 )
	{
		printf ("Usage : %s \"sample.(ogg|wav)\"\n", argv[0]);
        printf ("\tSpecify a sample file to play\n\n");
        exit(1);
	}
	else
	{
		strFilename.assign(argv[1]);
	}

	cOAL_Sample *pSample = NULL;

    printf ("Initializing OpenAL... ");
    fflush(stdout);
    OAL_SetupLogging(true,eOAL_LogOutput_File,eOAL_LogVerbose_High);

    cOAL_Init_Params oal_parms;

    if (OAL_Init(oal_parms)==false)
    {
        printf ("Failed - Check your OpenAL installation\n");
        return 0;
    }
    else
	{
        printf ("Success\n");
	}

    printf ("Loading sample (via file handlers) \"%s\" ... ", strFilename.c_str());

    pSample = OAL_Sample_Load (strFilename);

	playSample(pSample);
	
	if (pSample) OAL_Sample_Unload ( pSample );
	
	printf("Testing loading from memory buffer ...");
	FILE *fp = fopen(strFilename.c_str(), "rb");
	fseek(fp, 0, SEEK_END);
	size_t pos = ftell(fp);
	fseek(fp, 0, SEEK_SET);

	void *buffer = malloc(pos);
	
	fread(buffer, pos, 1, fp);
	fclose(fp);
	
	pSample = OAL_Sample_LoadFromBuffer(buffer, pos);
	free(buffer);

	playSample(pSample);
	
	if (pSample) OAL_Sample_Unload ( pSample );

    printf ("Cleaning up...\n");
    
    OAL_Close ();

	return 0;
}

