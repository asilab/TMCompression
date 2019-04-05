#!/bin/bash
#
# ==============================================================================
# Download Results in order to plot graphics
# ==============================================================================


function gdrive_download () {
  CONFIRM=$(wget --quiet --save-cookies /tmp/cookies.txt --keep-session-cookies --no-check-certificate "https://docs.google.com/uc?export=download&id=$1" -O- | sed -rn 's/.*confirm=([0-9A-Za-z_]+).*/\1\n/p');
  wget --load-cookies /tmp/cookies.txt "https://docs.google.com/uc?export=download&confirm=$CONFIRM&id=$1" -O $2 -P ../resultText;
  rm -rf /tmp/cookies.txt;
}

gdrive_download 1AEp4Zw5kvlBF_52-K_qTyYkzHAIPYBad 2sts2alp.txt;
gdrive_download 1cm2xRDoeruGsFlTeI4SxEM7f32wN0nnT 2sts3alp.txt;
gdrive_download 1XN4yo-nWUf_nAG6jEhVcWk2sQ4-R_N3t 3sts2alp.txt;
gdrive_download 17TgxM1FOJ2fKD-47qmwGA0IvRADXDjlK 4sts2alp.txt;
gdrive_download	1t-dTEBpoACgsmY05JA3KayIRpuPJqJPT 5sts2alp.txt;
gdrive_download 16Ag9auL03fzsli0znhSkz73yXlJ4EFN6 6sts2alp.txt;

gdrive_download 1tJY0TbWINyuaGqI1FUA-pphjy9_nmwV7 InterestingTM2sts2alp.txt;
gdrive_download 1-UE3koaleGP6aQwIZw9crLRBbeGE6gMF InterestingTM2sts3alp.txt;
gdrive_download 1EGs6w3U5Gf57ztRSwgHl0-gtfBfgrM3g InterestingTM3sts2alp.txt;
gdrive_download 1CNBo0Tkl3t5vhlfive8ayh4-QGna2IwY InterestingTM4sts2alp.txt;
gdrive_download	1hGo7XXVM6WN6CpufnSvQ7fgHk3Fy6sMu InterestingTM5sts2alp.txt;
gdrive_download 1_B_bE7vB8umHMm62YS2WChckOeCSIrlG InterestingTM6sts2alp.txt;

