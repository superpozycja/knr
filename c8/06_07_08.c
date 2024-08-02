#include <stddef.h>
#include <unistd.h>
#define NALLOC 1024

#undef malloc
#undef free

typedef long Align;

typedef union header {
	struct {
		union header *ptr;
		unsigned size;
	} s;
	Align x;
} Header;

static Header base;
static Header *freep = NULL;

void free(void *ap)
{
	if (((Header *)ap)->s.size == 0)
		return;
	Header *bp, *p;
	bp = (Header *)ap - 1;
	for (p = freep; !(bp > p && bp < p->s.ptr); p = p->s.ptr)
		if (p >= p->s.ptr && (bp > p || bp < p->s.ptr))
			break;
	if (bp + bp->s.size == p->s.ptr) {
		bp->s.size += p->s.ptr->s.size;
		bp->s.ptr = p->s.ptr->s.ptr;
	} else {
		bp->s.ptr = p->s.ptr;
	}
	if (p + p->s.size == bp) {
		p->s.size += bp->s.size;
		p->s.ptr = bp->s.ptr;
	} else {
		p->s.ptr = bp;
	}
	freep = p;
}

static Header *morecore(unsigned int nu)
{
	char *cp;
	Header *up;

	if (nu < NALLOC)
		nu = NALLOC;
	cp = sbrk(nu * sizeof(Header));
	if (cp == (char *) - 1)
		return NULL;
	up = (Header *) cp;
	up->s.size = nu;
	free((void *)(up + 1));
	return freep;
}

void *malloc(unsigned int nbytes)
{
	Header *p, *prevp;
	unsigned int nunits;

	if (nbytes <= 0)
		return NULL;

	nunits = (nbytes+sizeof(Header)-1)/sizeof(Header) + 1;

	if ((prevp = freep) == NULL) {
		base.s.ptr = prevp = freep = &base;
		base.s.size = 0;
	}

	for (p = prevp->s.ptr; ; prevp = p, p = p->s.ptr) {
		if (p->s.size >= nunits) {
			if (p->s.size == nunits) {
				prevp->s.ptr = p->s.ptr;
			} else {
				p->s.size -= nunits;
				p += p->s.size;
				p->s.size = nunits;
			}
			freep = prevp;
			return (void *)(p+1);
		}
		if (p == freep)
			if ((p = morecore(nunits)) == NULL)
				return NULL;
	}
}

void *calloc(unsigned int n, unsigned int size)
{
	char *c, *d;
	int i;
	c = malloc(n*size);

	if (c)
		for (d = c, i = 0; i < n*size; i++) {
			*c++ = 0;
		}
	return c;
}

void bfree(char *p, unsigned int n)
{
	Header *header_p = (Header *)p;
	header_p->s.size = n / sizeof(Header);
	free((void *) (header_p + 1));
}

int main()
{

}
