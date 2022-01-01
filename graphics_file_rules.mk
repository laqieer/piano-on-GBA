GFXDIR := graphics

$(CASTFORMGFXDIR)/keyboard_61.4bpp: %.4bpp: %.png
	$(GFX) $< $@

$(CASTFORMGFXDIR)/keyboard_61.gbapal: %.gbapal: %.pal
	$(GFX) $< $@
