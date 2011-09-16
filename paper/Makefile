DOCUMENT_NAME = maye12curb
BIB_DIR = bib
MAIN_FILE = main
SRC_DIR = src
OUTPUT_DIR = output

.PHONY:	draft final clean

$(OUTPUT_DIR)/$(DOCUMENT_NAME).dvi:	$(SRC_DIR)/*.tex $(MAIN_FILE).tex $(BIB_DIR)/*.bib
	latex -output-directory=$(OUTPUT_DIR) -jobname=$(DOCUMENT_NAME) $(MAIN_FILE)
	bibtex $(OUTPUT_DIR)/$(DOCUMENT_NAME)
	latex -output-directory=$(OUTPUT_DIR) -jobname=$(DOCUMENT_NAME) $(MAIN_FILE)
	latex -output-directory=$(OUTPUT_DIR) -jobname=$(DOCUMENT_NAME) $(MAIN_FILE)

draft:	$(OUTPUT_DIR)/$(DOCUMENT_NAME).dvi
	touch $(MAIN_FILE).tex
	make $(OUTPUT_DIR)/$(DOCUMENT_NAME).dvi

final:	$(OUTPUT_DIR)/$(DOCUMENT_NAME).dvi
	dvips -Ppdf -G0 -tletter $(OUTPUT_DIR)/$(DOCUMENT_NAME) -o $(OUTPUT_DIR)/$(DOCUMENT_NAME).ps
	ps2pdf -dCompatibilityLevel=1.4 -dMAxSubsetPct=100 -dSubsetFonts=true -dEmbedAllFonts=true -sPAPERSIZE=letter $(OUTPUT_DIR)/$(DOCUMENT_NAME).ps $(OUTPUT_DIR)/$(DOCUMENT_NAME).pdf

clean:
	rm -rf $(OUTPUT_DIR)/*.dvi $(OUTPUT_DIR)/*.log $(OUTPUT_DIR)/*.aux $(OUTPUT_DIR)/*.bbl $(OUTPUT_DIR)/*.blg $(OUTPUT_DIR)/*.pdf $(OUTPUT_DIR)/*.ps
