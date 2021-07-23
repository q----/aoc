#!/bin/perl

my $file = 'input';
open my $info, $file or die "AAAAAAAAAAAAAAAA";

sub part1{
  my $t = $_[0];
  foreach(('byr','iyr','eyr','hgt','hcl','ecl','pid')){
    return '' if not $t =~ /${_}/;
  }
  return 1;
}

sub Valid{
  my $t = $_[0];
  return '' if not $t =~ /(byr:((19[^01]\d)|(200[012])))/;
  return '' if not $t =~ /(iyr:20((1\d)|(20)))/;
  return '' if not $t =~ /(eyr:20((2\d)|(30)))/;
  return '' if not $t =~ /(hgt:((1(([5-8]\d)|(9[0-3]))cm)|(((59)|(6\d)|(7[0-6]))in)))/;
  return '' if not $t =~ /(hcl:#[0-9a-f]{6} )/;
  return '' if not $t =~ /(ecl:((amb)|(blu)|(brn)|(gry)|(grn)|(hzl)|(oth)))/;
  return '' if not $t =~ /(pid:\d{9} )/;
  return 1;
}

my $p1 = 0;
my $valid = 0;
my $string = "";
while(my $line = <$info>){
  chomp($line);
  if($line eq ""){
    $p1++ if part1($string);
    $valid++ if Valid($string);
    $string = "";
  } else {
    $string = "${string} ${line} ";
  }
}
$p1++ if part1($string);
$valid++ if Valid($string);

print $p1 . "\n";
print $valid . "\n";

close $info;
