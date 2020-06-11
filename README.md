# AVL Tree - Web links

Implements the AVL Tree data structure in order to store web pages IDs and their links to other web pages.  
Every node(Web page ID) in the AVL Tree points to another AVL Tree which contain's the node's links to other web pages.  Basically an AVL Tree with web pages IDs.  
The program reads the data from the input file and exports a text file which contains all the IDs with their total links to other web pages and all its links.  
  

**Input file structure:**  
<*Web_page_IDi>\t<Web_page_IDj*>   
<*Web_page_IDi>\t<Web_page_IDj*>   
...   
  
e.g.: 1\t2   
Web page with ID=1 **has a link** to web page with ID=2.  

  
**Output file structure:**  
<*Web_page_IDi>, <total_links_of_web_page>, <link_ID1>, <link_ID2>, ..., <link_IDn*>   
<*Web_page_IDj>, <total_links_of_web_page>, <link_ID1>, <link_ID2>, ..., <link_IDn*>   
...   
  
e.g.: 12, 2, 236, 237  
Web page with ID=12 **has 2 links** to other web pages. A link to web page with ID=236 and a link to web page with ID=237.  

Program doesn't read anything from the keyboard! All commands are read from the file "commands.txt".  
  
**Commands:**  
*READ_DATA <name_of_input_file>*  
*INSERT_LINK <Web_page_ID> <Web_page_ID>*  
*DELETE_LINK <Web_page_ID> <Web_page_ID>*  
*WRITE_INDEX <name_of_output_file>*  


*This project was created for a 2nd semester course.*  
