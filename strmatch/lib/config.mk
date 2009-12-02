SSE42=$(shell grep sse4.2 /proc/cpuinfo |uniq )
SSE2=$(shell grep sse2 /proc/cpuinfo |uniq )
ifneq ($(strip $(SSE42)),)
	SSE42=yes
else
	SSE42=no
endif

ifneq ($(strip $(SSE2)),)
	SSE2=yes
else 
	SSE2=no
endif
