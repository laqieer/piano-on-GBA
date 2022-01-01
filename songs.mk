STD_REVERB = 50

$(MID_BUILDDIR)/%.o: $(MID_SUBDIR)/%.s
	$(AS) $(ASFLAGS) -I sound -o $@ $<

$(MID_SUBDIR)/edward_elgar_salut_d_amour_piano_solo.s: %.s: %.mid
	$(MID) $< $@ -E -R$(STD_REVERB) -G005 -V080 -P1
