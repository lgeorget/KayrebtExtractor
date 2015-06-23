#!/usr/bin/perl
#

use strict;
use warnings;

my $function;
my $output;

my $newdir = ".";
if (@ARGV > 0) {
	$newdir = $ARGV[0];
}
print "outputting to dir '$newdir'\n";

while (<STDIN>)
{
	if (/^Function (.+)$/)
	{
		$function = $1;
		open($output, ">", "$newdir/$function.dot") or warn "Couldn't open output file for $function";
	}
	elsif (/digraph d/ ... /^\}$/)
	{
		print $output $_ if ($output);
	}
	else
	{
		close $output if $output;
	}
}
0;
