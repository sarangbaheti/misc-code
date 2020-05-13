simple.bsc: *.sbr
   bscmake /Iu /o simple.bsc *.sbr

STUFF: $(TARGET)
   c:\winice95\nmsym /trans:source,package,always $(TARGET)
!if "$(OS)" == "NT"
   copy $(TARGET) $(WINDIR)\system32\drivers
!else
   copy $(TARGET) $(WINDIR)\system
!endif
