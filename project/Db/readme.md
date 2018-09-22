# Db


**you can find an exemple in exemple.cpp**

db::Key = std::size_t;

template<typename T>
db::serializer_t = void (*)(T const &, Element &, db::Db &);

template<typename T>
db::deserializer_t = T (*)(Element &, db::Db &);


## class db::Db

db::createTable(tableName, descriptions, serializer, deserializer)
create the table format to use it (you can't use a table if you've not create it).
tableName : name of table
description : list of dataName and it type
serializer : function that can serialize this table (not mandatory)
deserializer : function that can deserialize this table (not mandatory)

template< typename T >
db::db::get<T>(key)
deserialize the type T from the table.
key : key of the element to get

template< typename T >
db::db::insert<T>(element)
serialize the type T in the table.
element : object you want put in the database

db::db::operator [] (tableName)
give you a table.
tableName : name of the table you want


## class db::Table

db::Table::setDescription(dataName, type)
add dynamically a data description
dataName : name of data
type : type of data

template< typename T >
db::Table::setSerializer<T>(serializer)
set/reset dynamically a serializer of this table.

template< typename T >
db::Table::setDeserializer<T>(deserializer)
set/reset dynamically a deserializer of this table.

db::Table::newElement()
create a new element in the table and return his Key.

db::Table::operator [] (key)
give you the an element of the table.
key : key of the element you want

## class db::Element

db::Element::operator [] (dataName)
give you the an data of the element.
dataName : name of the data you want (you can modify it)