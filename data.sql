create table computer(
    vname primary key,
    width int,
    height int,
    cname varcahr(20)
);

create table object(
    idx int primary key,
    oname varchar(20) not null,
    cname varchar(20),
    foreign key(cname) 
    references computer(cname) 
    on delete cascade 
    on update cascade
);

create table video(
    vname varchar(20),
    width int,
    height int,
    cname varchar(20),
    primary key(vname,cname),
    foreign key(cname)
    references computer(cname)
    on delete cascade 
    on update cascade
);

