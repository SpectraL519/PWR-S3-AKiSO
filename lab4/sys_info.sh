# Lab 4 - exercise 2
# This script displays system info every second

#!/bin/bash

net_lines=$(cat /proc/net/dev | wc -l)

# Use seq 3 to include lo interface and seq 4 not to
calculateNetDownload() {
	sum=0
	for i in `seq 3 $net_lines`; do
	    dev_line=($(awk -v line="$i" 'NR==line {print;exit}' /proc/net/dev))
        sum=$((sum + ${dev_line[1]}))
	done

	echo "$sum"
}

calculateNetUpload() {
	sum=0
	for i in `seq 3 $net_lines`; do
	    dev_line=($(awk -v "line=$i" 'NR==line {print;exit}' /proc/net/dev))
        sum=$((sum + ${dev_line[9]}))
	done

	echo "$sum"
}

convertUnits() {
	if [ $(($(($1/1024))/1024)) -ge 1 ]; then
        echo "$(($(($1/1024))/1024)) MB"
	elif [ $(($1/1024)) -ge 1 ]; then
        echo "$(($1/1024)) KB"
	else
        echo "$1 B"
	fi
}

cpuUsageTotal () {
    value=($(cat /proc/stat | grep $1 -w | awk '{print ($2+$3+$4+$5+$6+$7+$8+$9+$10)}'))
    echo $value
}

cpuUsageIdle () {
    value=($(cat /proc/stat | grep $1 -w | awk '{print ($5)}'))
    echo $value
}



# Net data - init
init_upload="$(calculateNetUpload)"
init_download="$(calculateNetDownload)"
prev_upload=$init_upload
prev_download=$init_download

download_history=()
upload_history=()
for i in 0 1 2 3 4 5; do
	download_history+=("0")
	upload_history+=("0")
done
plot_width=25

# CPU data - init
declare -A cpu_prev_total
declare -A cpu_prev_idle
cpu_freq=$(echo $(cat /proc/cpuinfo | grep MHz | cut -d ":" -f2))
i=0
for freq in $cpu_freq; do
	cpu="cpu${i}"
	cpu_prev_total[$cpu]=$(cpuUsageTotal $cpu)
	cpu_prev_idle[$cpu]=$(cpuUsageIdle $cpu)	
	i=$((i + 1))
done
declare -A cpu_curr_usage


loop=0
while true; do
	loop=$((loop + 1))

	# Net data
	upload="$(calculateNetUpload)"
	curr_upload=$((upload - prev_upload))
	prev_upload=$upload
	avg_upload=$(($((upload - init_upload))/$loop))
	upload_converted=$(convertUnits $((curr_upload)))
	avg_upload_converted=$(convertUnits $((avg_upload)))
	download="$(calculateNetDownload)"
	curr_download=$((download - prev_download))
	prev_download=$download
	avg_download=$(($((download - init_download))/$loop))
	download_converted=$(convertUnits $((curr_download)))
	avg_download_converted=$(convertUnits $((avg_download)))

	upload_history=("${upload_history[@]:1}")
	upload_history+=($((curr_upload)))
	download_history=("${download_history[@]:1}")
	download_history+=($((curr_download)))

	max_upload=${upload_history[0]}
	for u in "${upload_history[@]}"; do
		if [ "$u" -gt "$max_upload" ] ; then
			max_upload=$u
		fi 
	done
	if [ "$max_upload" -eq "0" ]; then
		max_upload=1;
	fi

	max_download=${download_history[0]}
	for d in "${download_history[@]}"; do
		if [ "$d" -gt "$max_download" ] ; then
			max_download=$d
		fi 
	done
	if [ "$max_download" -eq "0" ]; then
		max_download=1;
	fi


    # CPU data
    cpu_freq=$(echo $(cat /proc/cpuinfo | grep MHz | cut -d ":" -f2))
	i=0
	for freq in $cpu_freq; do
		cpu="cpu${i}"

		total=$(cpuUsageTotal $cpu)
		idle=$(cpuUsageIdle $cpu)

		total_per_loop=$(($total-${cpu_prev_total[$cpu]}))
		idle_per_loop=$(($idle-${cpu_prev_idle[$cpu]}))

		cpu_curr_usage[$cpu]=$((100-$idle_per_loop*100/$total_per_loop))
		
		cpu_prev_total[$cpu]=$total
		cpu_prev_idle[$cpu]=$idle

		i=$((i + 1))
	done

	# System uptime
	time=($(awk 'NR==1 {print;exit}' /proc/uptime))
	get_seconds=(${time//./ })
	seconds=$((get_seconds%60))
	get_minutes=$((get_seconds/60))
	minutes=$((get_minutes%60))
	get_hours=$((get_minutes/60))
	hours=$((get_hours%60))
	days=$((get_hours/24))

	# Battery capacity
	battery_data=($(awk 'NR==13 {print;exit}' /sys/class/power_supply/BAT1/uevent))
	battery_capacity=(${battery_data//=/ })

	# System load
	load=$(awk 'NR==1 {print $1}' /proc/loadavg)

	# total memory usage
	memory_1=($(awk 'NR==1 {print;exit}' /proc/meminfo))
	memory_2=($(awk 'NR==2 {print;exit}' /proc/meminfo))
	memory_total=${memory_1[1]}
	memory_free=${memory_2[1]}
	memory_used=$((memory_total - memory_free))


	clear

    echo "SYSTEM INFO"

    echo
    echo "Net data:"
	(printf "\tUpload: %s\n" "$upload_converted"
	printf "\tAverage Upload: %s\n" "$avg_upload_converted"
	for u in "${upload_history[@]}"; do
		fields=$((u*plot_width/max_upload))
		bar="printf '█%.0s' {1..$fields}"
		printf "\t\t|"; tput setaf 2; eval $bar; tput setaf 7; printf "| %s\n" "$(convertUnits $(($u)))"
	done

	echo
	printf "\tDownload: %s\n" "$download_converted"
	printf "\tAverage Download: %s\n" "$avg_download_converted")
	printf "\tDownload history:\n"
	for d in "${download_history[@]}"; do
		fields=$((d*plot_width/max_download))
		bar="printf '█%.0s' {1..$fields}"
		printf "\t\t|"; tput setaf 2; eval $bar; tput setaf 7; printf "|%s\n" "$(convertUnits $(($d)))"
	done

    echo
	echo "CPU data:"
	(printf "\tCPU | Usage | Clock speed\n"
	i=0
    for freq in $cpu_freq; do
		cpu="cpu${i}"
        printf "\t%s | %s | %s MHz\n" "$i" "${cpu_curr_usage[$cpu]}%" "$freq"
        i=$((i + 1))
    done) | column -t -s "|"

    echo
    printf "System uptime: %sd:%sh:%sm:%ss\n" "$days" "$hours" "$minutes" "$seconds"

    echo
	echo "Battery percentage: ${battery_capacity[1]}%"

    echo
	echo "System load: $load"

    echo
	echo "Memory used: $memory_used b"

	sleep 1
done