#/bin/sh

for i in *.dot
do
	dot $i -Tpng > $(basename $i .dot).png
done
