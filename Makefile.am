## Process this file with automake to produce Makefile.in 

SUBDIRS = Source_Files tools data

# Requires automake 1.5
AUTOMAKE_OPTIONS = 1.5 foreign dist-bzip2 no-dist-gzip

EXTRA_DIST = COPYING.SDL INSTALL.BeOS INSTALL.Unix INSTALL.Windows	\
  Makefile.BeOS docs/MML.html docs/Lua.html docs/Lua_HUD.html		\
  data/Fonts Resources/Windows/alephone.ico				\
  Resources/Windows/alephone.rc						\
  Resources/Windows/marathon.rc Resources/Windows/marathon.ico          \
  Resources/Windows/marathon2.rc Resources/Windows/marathon2.ico        \
  Resources/Windows/marathon-infinity.rc                                \
  Resources/Windows/marathon-infinity.ico                               \
  PBProjects/AlephOne.xcodeproj/project.pbxproj				\
  PBProjects/English.lproj/InfoPlist.strings PBProjects/FilmIcon.icns	\
  PBProjects/ImagesIcon.icns PBProjects/MapIcon.icns			\
  PBProjects/MMLIcon.icns PBProjects/MusakIcon.icns			\
  PBProjects/PhysIcon.icns			                        \
  PBProjects/SaveIcon.icns PBProjects/ShapesIcon.icns			\
  PBProjects/SoundsIcon.icns PBProjects/Info-AlephOne_SDL.plist		\
  PBProjects/precompiled_headers.h PBProjects/SDLMain.h			\
  PBProjects/SDLMain.m PBProjects/AlephOne.icns				\
  Expat/xmltok/nametab.h PBProjects/config.h PBProjects/confpaths.h	\
  data/AlephJPSansMono-Bold.ttf data/AlephJPSansMonoLicense.txt		\
  docs/alephone.6 examples/lua/Cheats.lua THANKS			\
  data/powered-by-alephone.svg						\
  PBProjects/AlephOne-Xcode4.xcodeproj/project.pbxproj\
  PBProjects/AlephOne-Xcode4.xcodeproj/project.xcworkspace/contents.xcworkspacedata\
  PBProjects/Info-AlephOne-Xcode4.plist\
	PBProjects/AppStore/Marathon/Marathon.plist \
	PBProjects/AppStore/Marathon/Marathon.icns \
	PBProjects/AppStore/Marathon/English.lproj/InfoPlist.strings

man_MANS = docs/alephone.6

dist-hook: AlephOne.spec
	cp AlephOne.spec $(distdir)
	cp "$(srcdir)/Aleph One Classic SDL.mcp" $(distdir)
	cp "$(srcdir)/Resources/Aleph One Classic SDL.r" $(distdir)/Resources
	mkdir -p "$(distdir)/PBProjects/AppStore/Marathon 2/English.lproj"
	cp "$(srcdir)/PBProjects/AppStore/Marathon 2/Marathon 2.plist" "$(distdir)/PBProjects/AppStore/Marathon 2/"
	cp "$(srcdir)/PBProjects/AppStore/Marathon 2/Marathon 2.icns" "$(distdir)/PBProjects/AppStore/Marathon 2/"
	cp "$(srcdir)/PBProjects/AppStore/Marathon 2/English.lproj/InfoPlist.strings" "$(distdir)/PBProjects/AppStore/Marathon 2/English.lproj/"
	mkdir -p "$(distdir)/PBProjects/AppStore/Marathon Infinity/English.lproj"
	cp "$(srcdir)/PBProjects/AppStore/Marathon Infinity/Marathon Infinity.plist" "$(distdir)/PBProjects/AppStore/Marathon Infinity/"
	cp "$(srcdir)/PBProjects/AppStore/Marathon Infinity/Marathon Infinity.icns" "$(distdir)/PBProjects/AppStore/Marathon Infinity/"
	cp "$(srcdir)/PBProjects/AppStore/Marathon Infinity/English.lproj/InfoPlist.strings" "$(distdir)/PBProjects/AppStore/Marathon Infinity/English.lproj/"


$(PACKAGE)-$(VERSION)-MacWinLibs-Src.tar.bz2: Libraries
	tar cjf $(PACKAGE)-$(VERSION)-MacWinLibs-Src.tar.bz2 -C $(srcdir) --exclude '.svn' Libraries 

libsrc: $(PACKAGE)-$(VERSION)-MacWinLibs-Src.tar.bz2

release: dist windist libsrc

# Rule to build RPM distribution package
rpm: $(PACKAGE)-$(VERSION).tar.gz
	rpmbuild -ta --clean $(PACKAGE)-$(VERSION).tar.gz

ChangeLog:
	svn2cl --break-before-msg

# Rules to build Windows zipfiles
WINZIP=$(PACKAGE)-$(VERSION)-Win.zip
M1_WINZIP=Marathon-$(VERSION)-Win.zip
M2_WINZIP=Marathon2-$(VERSION)-Win.zip
MINF_WINZIP=MarathonInfinity-$(VERSION)-Win.zip

M1_WINUP=Marathon-$(VERSION)-Exe-Win.zip
M2_WINUP=Marathon2-$(VERSION)-Exe-Win.zip
MINF_WINUP=MarathonInfinity-$(VERSION)-Exe-Win.zip

winzip: $(WINZIP)
m1-winzip: $(M1_WINZIP)
m2-winzip: $(M2_WINZIP)
inf-winzip: $(MINF_WINZIP)

m1-winup: $(M1_WINUP)
m2-winup: $(M2_WINUP)
inf-winup: $(MINF_WINUP)

windist: winzip m1-winzip m2-winzip inf-winzip m1-winup m2-winup inf-winup

# Windows directories


define cp_no_svn
mkdir -p "$(2)"
tar -c --exclude='.svn' -C "$(1)" . | tar -x -C "$(2)"
endef

define windist_common
unix2dos -n $(srcdir)/THANKS "$(1)/THANKS.txt"
unix2dos -n $(srcdir)/COPYING "$(1)/COPYING.txt"
unix2dos -n $(srcdir)/README "$(1)/README.txt"
mkdir "$(1)/docs"
cp $(srcdir)/docs/Lua.html "$(1)/docs/Lua.html"
cp $(srcdir)/docs/Lua_HUD.html "$(1)/docs/Lua_HUD.html"
cp $(srcdir)/docs/MML.html "$(1)/docs/MML.html"
$(call cp_no_svn,$(srcdir)/data/default_theme,$(1)/Themes/Default)
mkdir "$(1)/Extras"
cp $(srcdir)/data/Software_Transparent_Liquids.mml "$(1)/Extras"
cp $(srcdir)/data/Transparent_Liquids.mml "$(1)/Extras"
cp $(srcdir)/data/Carnage_Messages.mml "$(1)/Extras"
unix2dos -n $(srcdir)/examples/lua/Cheats.lua "$(1)/Extras/Cheats.lua"
cp $(srcdir)/data/Fonts "$(1)/Fonts.fntA"
$(call cp_no_svn,$(srcdir)/Resources/Library Licenses,$(1)/docs/Library Licenses)
endef

# Windows version

WINDISTDIR=$(PACKAGE)-$(VERSION)
$(WINZIP): Source_Files/AlephOne.exe
	mkdir "$(WINDISTDIR)"
	$(call windist_common,$(WINDISTDIR))
	cp Source_Files/AlephOne.exe $(WINDISTDIR)/
	unix2dos -n $(srcdir)/INSTALL.Windows "$(WINDISTDIR)/docs/INSTALL.Windows.txt"
	cp $(srcdir)/data/Transparent_Sprites.mml $(WINDISTDIR)/Extras
	rm -f $(WINZIP)
	zip -r $(WINZIP) $(WINDISTDIR)
	rm -rf "$(WINDISTDIR)"

WINUPDIR_M1=Marathon-$(VERSION)
$(M1_WINUP): Source_Files/Marathon.exe
	mkdir "$(WINUPDIR_M1)"
	$(call windist_common,$(WINUPDIR_M1))
	cp Source_Files/Marathon.exe "$(WINUPDIR_M1)/Marathon.exe"
	rm -f $(M1_WINUP)
	zip -r $(M1_WINUP) "$(WINUPDIR_M1)"
	rm -rf "$(WINUPDIR_M1)"

WINDISTDIR_M1=Marathon (A1)
$(M1_WINZIP): Source_Files/Marathon.exe
	mkdir "$(WINDISTDIR_M1)"
	$(call windist_common,$(WINDISTDIR_M1))
	$(call cp_no_svn,$(srcdir)/data/Scenarios/M1A1,$(WINDISTDIR_M1))
	cp Source_Files/Marathon.exe "$(WINDISTDIR_M1)/Marathon.exe"
	rm -f $(M1_WINZIP)
	zip -r $(M1_WINZIP) "$(WINDISTDIR_M1)"
	rm -rf "$(WINDISTDIR_M1)"

WINUPDIR_M2=Marathon2-$(VERSION)
$(M2_WINUP): Source_Files/Marathon2.exe
	mkdir "$(WINUPDIR_M2)"
	$(call windist_common,$(WINUPDIR_M2))
	cp Source_Files/Marathon2.exe "$(WINUPDIR_M2)/Marathon 2.exe"
	rm -f $(M2_WINUP)
	zip -r $(M2_WINUP) "$(WINUPDIR_M2)"
	rm -rf "$(WINUPDIR_M2)"

WINDISTDIR_M2=Marathon 2
$(M2_WINZIP): Source_Files/Marathon2.exe
	mkdir "$(WINDISTDIR_M2)"
	$(call windist_common,$(WINDISTDIR_M2))
	$(call cp_no_svn,$(srcdir)/data/Scenarios/Marathon 2,$(WINDISTDIR_M2))
	$(call cp_no_svn,$(srcdir)/data/XBLA_HUD,$(WINDISTDIR_M2)/Plugins/XBLA_HUD)
	cp Source_Files/Marathon2.exe "$(WINDISTDIR_M2)/Marathon 2.exe"
	rm -f $(M2_WINZIP)
	zip -r $(M2_WINZIP) "$(WINDISTDIR_M2)"
	rm -rf "$(WINDISTDIR_M2)"


WINUPDIR_MINF=MarathonInfinity-$(VERSION)
$(MINF_WINUP): Source_Files/MarathonInfinity.exe
	mkdir "$(WINUPDIR_MINF)"
	$(call windist_common,$(WINUPDIR_MINF))
	cp Source_Files/MarathonInfinity.exe "$(WINUPDIR_MINF)/Marathon Infinity.exe"
	rm -f $(MINF_WINUP)
	zip -r $(MINF_WINUP) "$(WINUPDIR_MINF)"
	rm -rf "$(WINUPDIR_MINF)"

WINDISTDIR_MINF=Marathon Infinity
$(MINF_WINZIP): Source_Files/Marathon2.exe
	mkdir "$(WINDISTDIR_MINF)"
	$(call windist_common,$(WINDISTDIR_MINF))
	$(call cp_no_svn,$(srcdir)/data/Scenarios/Marathon Infinity,$(WINDISTDIR_MINF))
	$(call cp_no_svn,$(srcdir)/data/XBLA_HUD,$(WINDISTDIR_MINF)/Plugins/XBLA_HUD)
	cp Source_Files/MarathonInfinity.exe "$(WINDISTDIR_MINF)/Marathon Infinity.exe"
	rm -f $(MINF_WINZIP)
	zip -r $(MINF_WINZIP) "$(WINDISTDIR_MINF)"
	rm -rf "$(WINDISTDIR_MINF)"

FORCE:
