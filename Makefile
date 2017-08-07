MAKEFLAGS += --warn-undefined-variables
.DEFAULT_GOAL := all

DEBUG = false

### Edit these parameters ###

RM += -r

# Where your irssi include files live. You might need to install an
# 'irssi-dev' package or something like that.
IRSSI_DIST := $(shell echo $$IRSSI_INCLUDE)

MODULE_NAME = test

### You shouldn't need to edit anything beyond this point ###

SRCDIR = src/
SRCS := $(wildcard $(SRCDIR)/*.c)
HEAD := $(wildcard $(SRCDIR)/*.h)

CFLAGS = -Wall -Werror -g -D MODULE_NAME=\"$(MODULE_NAME)\"
LDFLAGS = -flat_namespace -undefined suppress -l curl

# When you start adding more components to your module, add them here.
LIBDIR = lib/
LIBS = lib$(MODULE_NAME).so
LIBS := $(addprefix $(LIBDIR)/,$(LIBS))

OBJDIR = obj/
OBJS := $(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(SRCS))
#OBJS := $(addprefix $(OBJDIR)/,$(OBJS))

INCLUDE = -I$(IRSSI_DIST) \
          -I$(IRSSI_DIST)/src \
          -I$(IRSSI_DIST)/src/fe-common/core \
          -I$(IRSSI_DIST)/src/core \
          -I$(IRSSI_DIST)/src/fe-text \
          -I$(IRSSI_DIST)/src/irc \
          -I$(IRSSI_DIST)/src/irc/core \
          -I$(IRSSI_DIST)/src/irc/dcc \
          -I$(IRSSI_DIST)/src/irc/notifylist


GLIB_CFLAGS = $(shell pkg-config glib-2.0 --cflags)

.PHONY: all
.DEFAULT: all
all: $(LIBS)

$(LIBS): $(OBJS) | $(LIBDIR)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

$(LIBDIR) $(OBJDIR) $(SRCDIR):
	mkdir -p $@

#.INTERMEDIATE: $(OBJS)
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) -c $(INCLUDE) -o $@ $< $(CFLAGS) $(GLIB_CFLAGS)


#install: $(LIBS)
#$(CC) $(CFLAGS) $(GLIB_CFLAGS) $(IRSSI_INCLUDE) -I $(SRC) -o $@ -fPIC -c $<
#install $< $(IRSSI_USER_DIR)/modules

.PHONY: clean
clean:
	$(RM) $(LIBDIR) $(OBJDIR)


.phony: clean install TAGS

test: all
	irssi --home=/private/var/home/msirabella/Documents/projects/discord/irssi
	
