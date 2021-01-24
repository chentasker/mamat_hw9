#!/usr/bin/env bash

cat $1 > tmp_rule_file.txt
sed -i 's/ //g' tmp_rule_file.txt

while IFS= read -r line; do
	#echo $line
	echo $line >> input_packets.txt
done

#cat input_packets.txt

while IFS= read -r line;
do
	rule=$(awk -F# '{print $1}' <<< $line)
	if [ -z "$rule" ]; then
		continue
	fi
	
	indexes=( 1 2 3 4)
	for i in "${indexes[@]}"
	do
		
		cur_rule=$(awk -v var=$i -F, '{print $var}' <<< "$rule")
		cat input_packets.txt | ./firewall.exe $cur_rule >> packets.txt 
		#while IFS= read -r inputline; do
		#	echo $inputline | ./firewall.exe $cur_rule >> packets.txt
		#done 
		sort packets.txt | uniq > sorted_packets.txt
		if [ $i -eq 1 ]; then
			cat sorted_packets.txt > collected_packets.txt
		else
			grep -f sorted_packets.txt collected_packets.txt > uniq_packets.txt
			rm collected_packets.txt
			cat uniq_packets.txt > collected_packets.txt
			rm uniq_packets.txt
		fi
		rm sorted_packets.txt
		rm packets.txt
	done
	cat collected_packets.txt >> output_packets.txt
done < tmp_rule_file.txt

sed -i 's/ //g' output_packets.txt
sort output_packets.txt | uniq
rm output_packets.txt
rm input_packets.txt
rm tmp_rule_file.txt