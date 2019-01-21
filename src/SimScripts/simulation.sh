#!/bin/sh

#print input arguments
echo "ON SHELL SCRIPT"
echo "first argument (length): $1"
echo "second argument (youngsModulus): $2"
echo "third argument: (poissonsRatio): $3"
echo "fourth argument: (jobName): $4"

# Execute abaqus cae without GUI command to start simulation with input parameters
# Carful, if you want to add more parameters , you need to add them here
#and set them in the python script accordingly
/usr/simulia/abaqus/Commands/abaqus cae noGUI=../src/SimScripts/beam.py -- $1 $2 $3 $4
/usr/simulia/abaqus/Commands/abaqus cae noGUI=../src/SimScripts/abaqus_read_odb.py -- $4

#Convert all images size to 80%
convert -resize 80% $4_step-0_S_S11_Iso.png $4_step-0_S_S11_Iso.png
convert -resize 80% $4_step-0_U_U1_Iso.png  $4_step-0_U_U1_Iso.png
convert -resize 80% $4_Xplot_step-beamLoad_x-ALLSE.png $4_Xplot_step-beamLoad_x-ALLSE.png
