mv *.txt ../resultText
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
gdrive_download 1s-5oiE76VDzcQTh7rHpzBfN1lmZjyFRE InterestingTM7sts2alp.txt;
gdrive_download 1pO8eCGOEflaOYMf8EvMgnWMhOLLgJQ5M InterestingTM8sts2alp.txt;
gdrive_download 1H--3xn98XFr0-Cm25TZIwj41jDfAw0i- InterestingTM9sts2alp.txt;
gdrive_download 1HezUZMZe4mrB-7oClmpLNLDelFHqHWmX InterestingTM10sts2alp.txt;


# Genome Sequences and NC of the sequences
gdrive_download 1h05197Ol3XjL9Sp-y8c1Lz3gfGbiLdxZ Parvovirus_virus_nc.txt;
gdrive_download 1v-vPH_vQIRqc_9WaiNSPnraYOFzehwC9 Parvovirus_virus_genome.txt;
gdrive_download 1mp3DibTheUpP5r-FGh97lT_37hZhmTuD Microplitis_demolitor_virus_nc.txt;
gdrive_download 15d3mo-0ujvax_01Z1GUlZD5l5lYLgOYn Microplitis_demolitor_virus_genome.txt;
gdrive_download 1Jyv5SoD2X8jV6C8c74tR80iqTp2c-AFw Herpes_simplex_virus_genome.txt;
gdrive_download 11I-iRgFzfpJ3rCL-ymrB2wfU16fHoBz- Herpes_simplex_virus_nc.txt;

mv *.txt ../resultText