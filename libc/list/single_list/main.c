#include "link_p.h"

int main()
{
	NODE_S* header = NULL;
	NODE_S* mid = NULL;
	int i = 0;

	//for (i = 0; i < 10; i++)
	//	top_append(&header, i);

	//for (i = 0; i < 10; i++)
	//	tail_append(&header, i);

	for (i = 0; i < 10; i++)
		tail_append_p(&header, i);

	print_link(header);

	del_node(&header, 8);

	turnover_link(&header);
	print_link(header);

	turnover_link1(&header);
	print_link(header);


	mid = find_mid(&header);
	printf("mid node data:%d\n", mid->m_nData);
	del_link(&header);
	print_link(header);
	return 0;
}
