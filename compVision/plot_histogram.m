function plot_histogram(h)
%   plot_histogram        plots a histogram given that the input is
%                         a histogram
%
%   Syntax:
%       plot_hitstogram(h)
%
%   Input:
%       h     = The histogram you want to plot
%
%   Output:
%       none.
%
%   History:
%       Jonathan Child      03/20/2012


bar(h);
miny = min(h);
maxy = max(h);
axis([1,256, miny,maxy]);
xlabel('intensity value');
ylabel('PMF');


end

