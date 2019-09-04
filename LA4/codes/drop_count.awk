# count the number of "d" in the Q2.tr file
# to find the number of packet loss

BEGIN {
  drop=0;
}

{
  if($1=="d") {
    drop++;
  }
}

END{
  printf("Total number of %s packets dropped due to congestion = %d\n",$5,drop);
}
