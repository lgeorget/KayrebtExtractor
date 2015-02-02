#!/usr/bin/perl
#

use strict;
use warnings;

my $function;
my $output;

while (<>)
{
	if (/^Function (\w+)/)
	{
		$function = $1;
		open($output, ">$function.dot") or warn "Couldn't open output file for $function";
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
