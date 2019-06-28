# SQLite Music

## Questions

2.1. ArtistID is made a foriegn key because it uniquely identifies the row for the table Artist serving as the primary key in it which
     allows the two tables to be relational in database.

2.2. The AlbumId is not used in Artist table to avoid redundancy as it's already accesible through the main Album table.The Artist
     table serves to identify the artist's name who has a unique Id(ArtistId). This unique Id then only needs to be used
     as a reference to the Artist table in the Album table.

2.3. For complex queries(eg join) string comparison(emails) is slower than integer comparison(Id). Moreover, if one uses email address
     as primary key in Customer table then it would have to be made a foriegn key in Invoice table or any
     other table refering a specific customer. In such case as a change in email address, all the tables would need to be modified
     with the new email address. It can also be more timely to write out email addresses as unique identification for different tasks as
     compared to integer values.

2.4. SELECT SUM(Total)
     FROM Invoice
     WHERE InvoiceDate LIKE '2010-__-__ __:__:__'

2.5. SELECT Name FROM Track WHERE TrackId IN
     (SELECT TrackId FROM InvoiceLine WHERE InvoiceId IN
     (SELECT InvoiceId FROM Invoice
     WHERE CustomerId = 50));


2.6. Make a new Composer table with unique Id(primary key) for each Composer and replace name of Composer in Track table with the Id
     assigned in Composer table and set this as the foriegn key.

## Debrief

a.  https://dev.mysql.com/doc/refman/5.6/en/any-in-some-subqueries.html
    https://www.w3schools.com/sql/sql_like.asp

b.  150 minutes
